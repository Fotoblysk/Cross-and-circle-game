/*! \file main.cpp
 *
 * \brief only main(). mainpage in.
 *
 * \author  Fotoblysk
 *
 * \date  2016/03/18 12:00
*/

/*! \mainpage
 * \brief Simple game.
 *
 * \note with gh-pages
 *
 * \author  Fotoblysk
 *
 * \version $Revision: 0.01 $
 *
 * \date  2016/03/13 21:44:00
 *
 * Contact: fotoblysk@fejm.pl
 *
 * Created on: Sun Mar 13 21:44:00 2016
 *
 * $Id: Cross-and-circle-game,v 0.01  21:44:00 bv Exp Fotoblysk$
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Game.h>
#include <thread>

//....!TO DO!....//////////////
//TODO(Foto):DONE 0.moving board via right mouse button.
//TODO(Foto):DONE1.Update doc. zooming wheel, mowing and zooming with keyboard, no more shared vars, enum BoardState,  EngineState.
//TODO(Foto):2.Update doc.
//TODO(Foto):DONE 3.Make menu - at least minimal.
//TODO(Foto):4.Size of board manually chosen.
//TODO(Foto):5.Net game/Ai.

//?to re-think
//:Dividing square from sf::RectangleShape.
//:Dividing Board from sf::Shape.
//?
//.....///////////////////////

/*!
 * \brief Runs RenderWindow. Runs game.
*/

int main() {
    // sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML window", sf::Style::Fullscreen/*,settings */);
    Game game(window);

    return 0;
}
