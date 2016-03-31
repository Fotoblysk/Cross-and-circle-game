#ifndef GAME_H
#define GAME_H
#include "Engine.h"
/*!
 * \brief Game main class. Class which is used run engine.
 * This class will menage menu and settings
*/
class Game
{
    public:
        Game(sf::RenderWindow& window);     ///< Initialization of RenderWindow& window - main window of the game.
        virtual ~Game();                    ///< Runs StartGame() function

    protected:

    private:
        Engine engine;                      ///<Main engine of the game
        sf::RenderWindow& window;           ///<Main game window
        sf::Event event;                    ///< Event object probably unused
        void startGame();                   ///< Runs engine starts multi player seats switch game.
};

#endif // GAME_H
