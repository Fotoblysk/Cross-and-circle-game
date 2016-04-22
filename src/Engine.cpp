#include "Engine.h"
#include <iostream>
#define HEIGHT 20
#define WIDTH 30

Engine::Engine()
:
    player_number(0),
    clicked(0),
    turn(nullptr)
{
    DEBUG_MSG("Engine removing"<<std::endl);
}

Engine::~Engine(){
    DEBUG_MSG("Engine removing"<<std::endl);
}

bool fullBoardCheck(sf::RenderWindow& window){

    return true;
}

void Engine::init(sf::RenderWindow& window){
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
    goodfoot.loadFromFile("fonts/goodfoot.ttf"); // font is a sf::Font
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
            state=Winner;
        }
    }
    if(state==PlayingGame)
        window.draw(board);
    else if(state==Winner)
    {
        window.setView(window.getDefaultView());
        std::string winning_msg="Winner is: ";
        std::string tmp="\n\nPress esc to return to menu.";
        winning_msg+=turn->toStr();
        winning_msg+=tmp;
        sf::Text text;
        text.setFont(goodfoot);

        text.setString(winning_msg);
        text.setCharacterSize(50);
        text.setColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(window.getSize().x/2.0-text.getLocalBounds().width/2.0,window.getSize().y/2.0-text.getLocalBounds().height/2.0);
        window.draw(text);
    }
}

void Engine::events(sf::RenderWindow& window,sf::Event& event){ //TODO(foto): make camera events moving zooming ectr. in different function
    static sf::Vector2i old_position;
    static bool screen_moving;
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
        if(event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
        {
            old_position=sf::Mouse::getPosition();
            if(!screen_moving)
                screen_moving=true;
            DEBUG_MSG(" right button - screen moving" << std::endl);
        }
        else if(event.type==sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Right)
        {
            screen_moving=false;
        }
    }
    if(screen_moving)
    {
        sf::Vector2i new_position=sf::Mouse::getPosition();
        //DEBUG_MSG(" mouse moved - right button: delta.x : " << -new_position.x+old_position.x<<std::endl<<
        //          "right button: delta.y : " << -new_position.y+old_position.y<<std::endl);
        view.setCenter(view.getCenter().x+(-new_position.x+old_position.x),view.getCenter().y+(-new_position.y+old_position.y));
        old_position=new_position;
        window.setView(view);
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
        state=EndOfGame;
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
