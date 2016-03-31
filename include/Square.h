#ifndef SQUARE_H
#define SQUARE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"
#define SQUARE_SIZE 50

#include<../debugging_tolls.h>



/*!
 * \brief Square class. Class which is used to build board
 * this class may be remade to inheritance from sf::RectangleShape
*/
class Square : public sf::Drawable, sf::Transformable
{
    friend class Board;
    public:
        Square();                                                   ///<sets pointers to NULL
        virtual ~Square();                                          ///<only DEBUG MSG
        Player* getMarkedBy() const;                                ///<function returning pointer to Player whose marked this Square(var - marked_by)
        void mark(Player *player_ptr);                              ///<this is function used by Board to set Square marked
        bool isMarked() const;                                      ///<returns true if square is marked(to rework)
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; ///<draws sf::RectangleShape square
    protected:

    private:
        void setTexture( sf::Texture *texture);                     ///<This is function used by current class to set Square(and sf::RectangleShape) current texture.
        virtual void setPosition(float x, float y);                 ///<Sets position of sf::RectangleShape square.

        Player* marked_by;                                          ///<variable used to save who marked current Square
        sf::RectangleShape square;                                  ///< Shape from SFML class. The whole class may inheritance form this class
        sf::Texture* texture;                                       ///<Pointer to current Square( sf::RectangleShape square ) texture. Marking change texture to player texture; this is going to be remade
};

#endif // SQUARE_H
