#include "Game.h"

Game::Game(sf::RenderWindow& in_window)
:
window(in_window)
{
    startGame();
}

Game::~Game()
{
    DEBUG_MSG("badass Game removing"<<std::endl);
}
void Game::startGame(){
    engine.init(window);
    while (window.isOpen())
    {

        window.clear();
        engine.events(window, event);
        engine.update(window);
        window.display();
    }
}
