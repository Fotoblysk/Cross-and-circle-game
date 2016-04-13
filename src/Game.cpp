#include "Game.h"

Game::Game(sf::RenderWindow& in_window)
:
window(in_window)
{
    goodfoot.loadFromFile("fonts/goodfoot.ttf"); // font is a sf::Font
    state=Menu;
    stateMachine();
}

Game::~Game()
{
    DEBUG_MSG("badass Game removing"<<std::endl);
}
void Game::stateMachine(){
    if(state==Menu)
        menu();
    else if(state==Play)
        startGame();
    else if(state==End)
        window.close();
}
void Game::startGame(){
    engine.init(window);
    while (window.isOpen()&&engine.currentState()!=Engine::EndOfGame)
    {
        window.clear();
        engine.events(window, event);
        engine.update(window);
        window.display();
    }
    state=Menu;
    stateMachine();
}
void Game::menu(){
    sf::Event event;
    sf::Text text_menu[2];
    window.setView(window.getDefaultView());
    text_menu[0].setString("Play Game");
    text_menu[1].setString("Exit");
    for(int i=0 ;i<2;i++)
    {
        text_menu[i].setFont(goodfoot);
        text_menu[i].setCharacterSize(50); // in pixels, not points!
        text_menu[i].setColor(sf::Color::White);
        text_menu[i].setStyle(sf::Text::Bold);
        text_menu[i].setPosition((window.getSize().x-text_menu[i].getLocalBounds().width)/2.0,(window.getSize().y-(2*(text_menu[0].getLocalBounds().height+50)))/2.0+i*(text_menu[0].getLocalBounds().height+50));
    }
    while(state==Menu)
    {
        window.clear();
        for(int i=0 ;i<2;i++)
            window.draw(text_menu[i]);
        menuEvents(event,text_menu);
        window.display();
    }
    stateMachine();
}
void Game::menuEvents(sf::Event& event,sf::Text* text_menu){
    mouse=sf::Mouse::getPosition(window);
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
           menuKeyboardEvents(event);
        }
        if (event.type == sf::Event::MouseMoved)
            menuMouseHilighting(event,text_menu);
        if(event.type == sf::Event::MouseButtonReleased && event.key.code==sf::Mouse::Left)
            menuMouseEvents(event,text_menu);
    }
}
void Game::menuKeyboardEvents(sf::Event& event){
    if (event.key.code == sf::Keyboard::Escape)
    {
        DEBUG_MSG( "the escape key was pressed in Game" << std::endl);
        DEBUG_MSG( "control:" << event.key.control << std::endl);
        DEBUG_MSG( "alt:" << event.key.alt << std::endl);
        DEBUG_MSG( "shift:" << event.key.shift << std::endl);
        DEBUG_MSG( "system:" << event.key.system << std::endl);
        state=End;
    }
}

void Game::menuMouseHilighting(sf::Event& event, sf::Text* text_menu){
    mouse_menu_position=0;
    for(int i=0 ;i<2;i++)
    {
        if (text_menu[i].getGlobalBounds().contains(mouse.x,mouse.y))
        {
            if(text_menu[i].getColor()!=sf::Color::Yellow)
                text_menu[i].setColor(sf::Color::Yellow);
                mouse_menu_position=i+1;
        }else{
            if(text_menu[i].getColor()!=sf::Color::White)
                text_menu[i].setColor(sf::Color::White);
        }
    }
}

void Game::menuMouseEvents(sf::Event& event, sf::Text* text_menu){
    if(mouse_menu_position!=0)
    {
        if (mouse_menu_position==1)
            state=Play;
        else if (mouse_menu_position==2)
            state=End;
    }
}
