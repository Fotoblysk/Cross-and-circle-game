#include "Board.h"
#include<iostream>
#include<assert.h>
Board::Board(){
    //ctor
    clicked=NULL;
    mouse=NULL;
    board_array=NULL;
    height=0;
    width=0;
}

Board::Board(int height_in, int width_in,sf::Vector2i* mouse_in){
    init(height_in, width_in,mouse_in);
}

Board::~Board(){
    if(board_array!=NULL){
        for(int height_index=0;height_index<height;height_index++)
            delete [] board_array[height_index];
        board_array=NULL;
    }
    DEBUG_MSG("badass Board removing"<<std::endl);

}

void Board::init(int height_in, int width_in,sf::Vector2i* mouse_in){
    clicked=NULL;
    width=width_in;
    height=height_in;
    texture.loadFromFile("textures/square_tex.png");
    board_array=new Square*[height_in];
    for(int height_index=0;height_index<height_in;height_index++)
        board_array[height_index]=new Square[width_in];
    for(int height_index=0;height_index<height;height_index++)
    {
        for(int width_index=0;width_index<width;width_index++)
        {
            board_array[height_index][width_index].setPosition(width_index*(SQUARE_SIZE+2),height_index*(SQUARE_SIZE+2));
            board_array[height_index][width_index].setTexture(&texture);
        }
    }
    mouse=mouse_in;
}


void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    states.transform *= getTransform();
    for(int height_index=0;height_index<height;height_index++)
    {
        for(int width_index=0;width_index<width;width_index++)
            target.draw(board_array[height_index][width_index]);
    }
}
bool Board::update(bool* clicked_in,Player** currrent_turn) {
    bool havent_any_failed=true;
    clicked=clicked_in;
    for(int height_index=0;height_index<height;height_index++)
    {
        for(int width_index=0;width_index<width;width_index++)
            if(!squareAction(height_index,width_index,currrent_turn))
                havent_any_failed=false;
    }
    return havent_any_failed;
}
bool Board::squareAction(int height_index, int width_index, Player** currrent_turn){
    if(board_array[height_index][width_index].square.getGlobalBounds().contains(mouse->x,mouse->y))
    {
        if(!board_array[height_index][width_index].isMarked()){ // marking and hillighting only fr ummarked squares
            mouse_hilighting=&(board_array[height_index][width_index]);
            if(board_array[height_index][width_index].square.getFillColor()!=sf::Color::Yellow)
                mouse_hilighting->square.setFillColor(sf::Color::Yellow);
            if(clicked&&*clicked)
                {   /// !!!! Tododododo have to  fix that
                mouse_hilighting->mark(*currrent_turn);
                checkWin( height_index, width_index, currrent_turn);
                    //now engine turns off clicked boolean :)
                }
        return true;
        }
        return false;
    }else if(board_array[height_index][width_index].square.getFillColor()!=sf::Color::White)
        board_array[height_index][width_index].square.setFillColor(sf::Color::White);
    return true;
}
bool Board::checkWin(int height_index,int width_index,Player** currrent_turn){
    /////////
    int counter=1;
    int i=1;
    assert(currrent_turn!=NULL&&*currrent_turn!=NULL);
    while(height_index+i<HEIGHT&&board_array[height_index+i++][width_index].getMarkedBy()==*currrent_turn)
        counter++;
    i=1;
    while(height_index-i>=0&&board_array[height_index-i++][width_index].getMarkedBy()==*currrent_turn)
        counter++;
    if(counter>=IN_A_ROW_TO_WIN)
        {
            DEBUG_MSG("ENDO GEJMO");
            exit(1);
            return true;
        }////////////////////////


    ///////////////////////
    counter=1;
    i=1;
    while(width_index+i<WIDTH&&board_array[height_index][width_index+i++].getMarkedBy()==*currrent_turn)
        counter++;
    i=1;
    while(width_index-i>=0&&board_array[height_index][width_index-i++].getMarkedBy()==*currrent_turn)
        counter++;
    if(counter>=IN_A_ROW_TO_WIN)
    {
        DEBUG_MSG("ENDO GEJMO");
        exit(1);
        return true;
    }
        ////////////////////

    ///////////////////////
    counter=1;
    i=1;
    while(width_index+i<WIDTH&&height_index+i<HEIGHT&&board_array[height_index+i][width_index+i++].getMarkedBy()==*currrent_turn)
        counter++;
    i=1;
    while(width_index-i>=0&&height_index-i>=0&&board_array[height_index-i][width_index-i++].getMarkedBy()==*currrent_turn)
        counter++;
    if(counter>=IN_A_ROW_TO_WIN)
        {
            DEBUG_MSG("ENDO GEJMO");
            exit(1);
            return true;
        }
        ////////////////////
    ///////////////////////
    counter=1;
    i=1;
    while(width_index-i>=0&&height_index+i<HEIGHT&&board_array[height_index+i][width_index-i++].getMarkedBy()==*currrent_turn)
        counter++;
    i=1;
    while(width_index+i<WIDTH&&height_index-i>=0&&board_array[height_index-i][width_index+i++].getMarkedBy()==*currrent_turn)
        counter++;
    if(counter>=IN_A_ROW_TO_WIN)
    {
        DEBUG_MSG("ENDO GEJMO");
        exit(1);
        return true;
    }
        ////////////////////

    return false;
}

