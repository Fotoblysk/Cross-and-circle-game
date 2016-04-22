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
class Square : public sf::RectangleShape
{
    friend class Board;
    public:
        Square();                                                   ///<sets pointers to nullptr
        virtual ~Square();                                          ///<only DEBUG MSG
        Player* getMarkedBy() const;                                ///<function returning pointer to Player whose marked this Square(var - marked_by)
        void mark(Player *player_ptr);                              ///<this is function used by Board to set Square marked
        bool isMarked() const;                                      ///<returns true if square is marked(to rework)

    protected:

    private:
        Player* marked_by;                                          ///<variable used to save who marked current Square
        sf::Texture* texture;                                       ///<Pointer to current Square( sf::RectangleShape square ) texture. Marking change texture to player texture; this is going to be remade
};

#endif // SQUARE_H
