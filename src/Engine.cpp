#include "Engine.h"
#include <iostream>
#define HEIGHT 20
#define WIDTH 30
Engine::Engine(){
    player_number=0;
    clicked=0;
    turn=NULL;
    zoom=1;
}

Engine::~Engine(){
    DEBUG_MSG("badass Engine removing"<<std::endl);
}
bool fullBoardCheck(sf::RenderWindow& window){

    return true;
}
void Engine::init(sf::RenderWindow& window)
{
    view=window.getDefaultView();
    state=PlayingGame;
    board.init(HEIGHT,WIDTH,mouse);
    window.draw(board);
    turn=&players[0];
    players[0].setTexture("textures/square_marked_circle.png");
    players[1].setTexture("textures/square_marked_cross.png");
    {
        const std::string player1Name("Player1");
        const std::string player2Name("Player2");
        players[0].setName(player1Name);
        players[1].setName(player2Name);
    }
}
void Engine::getMousePosition(sf::RenderWindow& window){
    mouse=static_cast<sf::Vector2i>(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
void Engine::update(sf::RenderWindow& window){
    getMousePosition(window);
    last_turn_board_state=board.update(clicked,turn,mouse);
    if(clicked)
    {
        if(last_turn_board_state==Board::NextTurn)
        {
            turn=&players[(++player_number)%=2]; ///unfortunately changes when there were player turn failed
            DEBUG_MSG("NEXT TURN : "<<turn->toStr()<<std::endl);
        }
        clicked=false;
        if(last_turn_board_state==Board::Winner)
        {
            std::cout<<std::endl<<"Winner is: "<<turn->toStr()<<std::endl;
            state=EndOfGame;
        }
    }
    window.draw(board);
}
void Engine::events(sf::RenderWindow& window,sf::Event& event){ //TODO(foto): make camera events moving zooming ectr. in different function
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::MouseWheelScrolled)
        {
            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                std::cout << "wheel type: vertical" << std::endl;
                DEBUG_MSG("scroll delta :"<<event.mouseWheelScroll.delta<<std::endl);
                view.zoom(1.00f - 0.1f*event.mouseWheelScroll.delta);
                window.setView(view);
            }
        }


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
    if (event.key.code == sf::Keyboard::Add)
    {
        view.zoom(0.9f);
        window.setView(view);
        DEBUG_MSG("zoomed"<<zoom<<std::endl);
    }
    if (event.key.code == sf::Keyboard::Subtract)
    {
        view.zoom(1.1f);
        window.setView(view);
        DEBUG_MSG("out zoomed"<<zoom<<std::endl);
    }
    if (event.key.code == sf::Keyboard::Up)
    {
        view.setCenter((view.getCenter().x),(view.getCenter().y-10.0f));
        window.setView(view);
        DEBUG_MSG("mooving up"<<std::endl);
    }
    if (event.key.code == sf::Keyboard::Down)
    {
        view.setCenter((view.getCenter().x),(view.getCenter().y+10.0f));
        window.setView(view);
        DEBUG_MSG("mooving down"<<std::endl);
    }
    if (event.key.code == sf::Keyboard::Right)
    {
        view.setCenter((view.getCenter().x+10.0f),(view.getCenter().y));
        window.setView(view);
        DEBUG_MSG("mooving right"<<std::endl);
    }
    if (event.key.code == sf::Keyboard::Left)
    {
        view.setCenter((view.getCenter().x-10.0f),(view.getCenter().y));
        window.setView(view);
        DEBUG_MSG("mooving left"<<std::endl);
    }

}
