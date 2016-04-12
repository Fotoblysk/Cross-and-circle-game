#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include <Board.h>
#include "Player.h"
#include<../debugging_tolls.h>
/*!
 * \brief Engine class. Class which manage main loop of game, reads keyboard events, update physics.
 * This class will menage menu and settings
*/
class Engine
{
    public:
        enum State {Start,Turn,Winner,End};             //TODO(FOTO#1#): LOL use it no exit()
        Engine();                                       ///<sets vars to neutral state, pointers to NULL
        virtual ~Engine();                              ///<only debug msg
        void init(sf::RenderWindow& window);            ///<initialization of Engine, sets player textures
        void update(sf::RenderWindow& window);          ///updates physics of the game,  draws board.
        void events(sf::RenderWindow& window,sf::Event& event); ///<reads events - all
    protected:
    private:
        Board board;                                    ///< contains dynamic allocated array of squares
        sf::Vector2i mouse;                             ///< current mouse position
        Player players[2];                              ///<just for tests array of players
        Player* turn;                                   ///< pointer to Player whose turn it is
        int player_number;                              ///< To fix .
        int number_of_players;                          ///< number of players
        bool clicked;                                   ///< var if lmouse button was clicked true else false
        bool last_turn_was_succesfull;                  ///< true if last turn was successful (no illegal action like marking already marked square)
        void getMousePosition(sf::RenderWindow& window);                ///< gets global mouse position
        void keyboardEvents(sf::RenderWindow& window,sf::Event& event); ///< reads keyboard events
        State state;                                    //TODO(FOTO#1#): LOL use it no exit()
};

#endif // ENGINE_H
