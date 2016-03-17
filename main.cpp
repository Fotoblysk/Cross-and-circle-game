//lol
#include <iostream>
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
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
