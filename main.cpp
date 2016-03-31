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


/*!
 * \brief Runs RenderWindow. Runs game.
*/
int main()
{
    sf::RenderWindow window(sf::VideoMode(500,500), "SFML window", sf::Style::Fullscreen );
    Game game(window);
    return 0;
}
