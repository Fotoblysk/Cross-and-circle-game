#include "Board.h"
#include<iostream>

Board::Board()
        :
        height(0),
        width(0),
        board_array(nullptr) {
    //ctor
}

Board::Board(int height_in, int width_in,
             sf::Vector2i &mouse_in) { // we get mouse_position reference only once to improve performence
    init(height_in, width_in, mouse_in);
}

Board::~Board() {
    if (board_array != nullptr) {
        for (int height_index = 0; height_index < height; height_index++)
            delete[] board_array[height_index];
        board_array = nullptr;
    }
    DEBUG_MSG("badass Board removing" << std::endl);

}

void Board::init(int height_in, int width_in, sf::Vector2i &mouse_in) {
    width = width_in;
    height = height_in;
    texture.loadFromFile("textures/square_tex.png");
    board_array = new Square *[height_in];
    for (int height_index = 0; height_index < height_in; height_index++)
        board_array[height_index] = new Square[width_in];
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            board_array[height_index][width_index].setPosition(width_index * (SQUARE_SIZE + 2) + MOVE_WIDTH,
                                                               height_index * (SQUARE_SIZE + 2) + MOVE_HEIGHT);
            board_array[height_index][width_index].setTexture(&texture);
        }
    }
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++)
            target.draw(board_array[height_index][width_index]);
    }
}

sf::Vector2i Board::getBoardPosition(sf::Vector2i mouse_position) {
    sf::Vector2i board_position;
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            if (board_array[height_index][width_index].getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                board_position.x = height_index;
                board_position.y = width_index;
            }
        }
    }
    return board_position;
}

Board::BoardState Board::update(bool &clicked, Player *currrent_turn, sf::Vector2i &current_mouse_position) {
    static sf::Vector2i last_board_position;
    BoardState state_tmp = NextTurn;
#ifndef NDEBUG
    sf::Vector2i positioner_tmp;
    positioner_tmp.x = 0;
    positioner_tmp.y = 0;
    positioner_tmp = getBoardPosition(current_mouse_position);
    if (positioner_tmp != last_board_position) {
        last_board_position = positioner_tmp;
        DEBUG_MSG("Position = " << last_board_position.x << "  ,  " << last_board_position.y << std::endl);
    }
#endif
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            state_tmp = updateField(clicked, height_index, width_index, currrent_turn, current_mouse_position);
            if (state_tmp != WaitingForTurn)// TODO(foto) fixxx
                return state_tmp;
        }
    }
    return state_tmp;
}

Board::BoardState Board::updateField(bool clicked, int height_index, int width_index, Player *currrent_turn,
                                     sf::Vector2i &current_mouse_position) {
    hilight(height_index, width_index, current_mouse_position);
    if (board_array[height_index][width_index].getGlobalBounds().contains(current_mouse_position.x,
                                                                          current_mouse_position.y)) {
        auto current_square_analiized = &(board_array[height_index][width_index]);
        if (!board_array[height_index][width_index].isMarked())  // marking and hillighting only fr ummarked squares
        {
            if (clicked) {
                makeMove(height_index, width_index , currrent_turn);
                return checkWin(height_index, width_index, currrent_turn);
            }
            return WaitingForTurn;
        }
        return WaitingForTurn;
    }
    return WaitingForTurn;
}

Board::BoardState Board::checkWin(int height_index_of_last_move, int width_index_of_last_move,
                                  Player *currrent_turn) const {
    /////////
    int counter = 1;
    int i = 1;
    assert(currrent_turn != nullptr);
    while (height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        //exit(1);
        return Winner;
    }


    ////////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move + i < WIDTH &&
           board_array[height_index_of_last_move][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        //exit(1);
        return Winner;
    }

    ////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move + i < WIDTH && height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move - i >= 0 && height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        // exit(1);
        return Winner;
    }

    ////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move - i >= 0 && height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move + i < WIDTH && height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        // exit(1);
        return Winner;
    }
    ////////////////////

    return NextTurn;
}

void Board::hilight(int height_index, int width_index, sf::Vector2i &current_mouse_position) {

    if (board_array[height_index][width_index].getGlobalBounds().contains(current_mouse_position.x,
                                                                          current_mouse_position.y)) {
        if (!board_array[height_index][width_index].isMarked())  // marking and hillighting only fr ummarked squares
        {
            auto current_square_to_hilight = &(board_array[height_index][width_index]);
            if (board_array[height_index][width_index].getFillColor() != sf::Color::Yellow)
                current_square_to_hilight->setFillColor(sf::Color::Yellow);
        }
    } else if (board_array[height_index][width_index].getFillColor() != sf::Color::White)
        board_array[height_index][width_index].setFillColor(sf::Color::White);

}

std::vector<std::string> Board::getBoardData() {

    return std::vector<std::string>();
}

bool Board::makeMove(int hight, int width, Player *player) {
    board_array[hight][width].mark(player);
    return false;
}
