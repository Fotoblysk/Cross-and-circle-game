#ifndef GAME_H
#define GAME_H
#define NUMBER_OF_MENU_BUTTONS 3
#include "Engine.h"
#include "NetworkEngine.h"
#include<../debugging_tolls.h>
#include<memory>
/*!
 * \brief Game main class. Class which is used run engine.
 * This class will menage menu and settings
*/
class Game
{
    enum GameState{Play, Options, Menu, End};
    public:
        Game(sf::RenderWindow& window);     ///< Initialization of RenderWindow& window - main window of the game.
        virtual ~Game();                       ///< Runs StartGame() function
    protected:

    private:
        sf::RenderWindow& window;           ///<Main game window
        sf::Event event;                    ///< Event object probably unused
        void startGame();                   ///< Runs engine starts multi player seats switch game.
        void menu();
        void menuMouseEvents(sf::Event& event, sf::Text* text_menu);
        void menuKeyboardEvents(sf::Event& event);
        void menuEvents(sf::Event& event, sf::Text* text_menu);
        void menuMouseHover(sf::Event& event, sf::Text* text_menu);
        void stateMachine();
        GameState state;
        sf::Font goodfoot;
        sf::Vector2i mouse;
        int mouse_menu_position;
};

#endif // GAME_H
