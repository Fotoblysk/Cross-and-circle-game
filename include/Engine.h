#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
//#include <SFML/Network>
#include <Board.h>
#include "Player.h"
#include<memory>
#include<../debugging_tolls.h>
/*!
 * \brief Engine class. Class which manage main loop of game, reads keyboard events, update physics.
 * This class will menage menu and settings
*/
class Engine
{
    public:
        enum EngineState{PlayingGame,Winner,EndOfGame};
        Engine();                                       ///<sets vars to neutral state, pointers to nullptr
        virtual ~Engine();                              ///<only debug msg
        virtual void init(sf::RenderWindow& window);            ///<initialization of Engine, sets player textures
        virtual void update(sf::RenderWindow& window);          ///updates physics of the game,  draws board.
        void events(sf::RenderWindow& window, sf::Event& event); ///<reads events - all
        EngineState currentState() const;
        //getRemoteTurn
        //connect();
    protected:
        Board board;                                    ///< contains dynamic allocated array of squares
        sf::Vector2i mouse;                             ///< current mouse position
        std::unique_ptr<Player> players[2];                              ///<just for tests array of players
        Player* turn;                                   ///< pointer to Player whose turn it is
        int current_player_number;                              ///< To fix .
        int number_of_players;                          ///< number of players
        bool clicked;                                   ///< var if lmouse button was clicked true else false
        Board::BoardState last_turn_board_state;                  ///< true if last turn was successful (no illegal action like marking already marked square)
        void getMousePosition(sf::RenderWindow& window);                ///< gets global mouse position
        void keyboardEvents(sf::RenderWindow& window, sf::Event& event); ///< reads keyboard events
        EngineState state;
        sf::View view;
        float zoom;
        sf::Font goodfoot;
        // select the font
};

#endif // ENGINE_H
