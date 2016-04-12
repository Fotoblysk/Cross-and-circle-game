#include "Engine.h"
#include <iostream>
#define HEIGHT 20
#define WIDTH 30
Engine::Engine(){
    last_turn_was_succesfull=true;
    player_number=0;
    clicked=0;
    turn=NULL;
}

Engine::~Engine(){
    DEBUG_MSG("badass Engine removing"<<std::endl);
}
bool fullBoardCheck(sf::RenderWindow& window){

    return true;
}
void Engine::init(sf::RenderWindow& window){
    board.init(HEIGHT,WIDTH,mouse);
    window.draw(board);
    turn=&players[0];
    players[0].setTexture("textures/square_marked_circle.png");
    players[1].setTexture("textures/square_marked_cross.png");
}
void Engine::getMousePosition(sf::RenderWindow& window){
    mouse=sf::Mouse::getPosition(window);
}
void Engine::update(sf::RenderWindow& window){
    getMousePosition(window);
    last_turn_was_succesfull=board.update(&clicked,turn,mouse);
    if(clicked)
    {
        if(last_turn_was_succesfull)// 2 circles in first turn
        {
            turn=&players[(++player_number)%=2]; ///unfortunatlly changes when there were player turn failed
            DEBUG_MSG("NEXT TURN : player "<<player_number<<std::endl);
        }
        clicked=false;
    }
    window.draw(board);
}
void Engine::events(sf::RenderWindow& window,sf::Event& event){
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
        {
           keyboardEvents(window,event);
        }
        if(event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            clicked=true;
            DEBUG_MSG(" lmouse button=" <<clicked<< std::endl);
        }
    }
}
void Engine::keyboardEvents(sf::RenderWindow& window,sf::Event& event){
    if (event.key.code == sf::Keyboard::Escape)
    {
        DEBUG_MSG( "the escape key was pressed" << std::endl);
        DEBUG_MSG( "control:" << event.key.control << std::endl);
        DEBUG_MSG( "alt:" << event.key.alt << std::endl);
        DEBUG_MSG( "shift:" << event.key.shift << std::endl);
        DEBUG_MSG( "system:" << event.key.system << std::endl);
        window.close();
    }
}
