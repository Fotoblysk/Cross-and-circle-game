#ifndef BOARD_H
#define BOARD_H
#include "Square.h"
#define IN_A_ROW_TO_WIN 5
#define HEIGHT 20
#define WIDTH 30
#include<../debugging_tolls.h>

//TODO(FOTO#1#): EXAMPLE5
/*!
 * \brief Engine class. Class which manage main loop of game, reads keyboard events, update physics.
 * This class will menage menu and settings
*/
class Board : public sf::Drawable, sf::Transformable
{
    public:
        Board();                                                ///<pointers to null . vars to  0. Board useless until  initialized with init(...)
        Board(int height_in, int width_in, sf::Vector2i* mouse_in); ///< inits board sets size and  mouse var allocates dynamic array of squares (runs init function).
        virtual ~Board();

        void init(int height_in, int width_in, sf::Vector2i* mouse_in); ///< inits board sets size and  mouse var

        bool update(bool* marked_in, Player* currrent_turn);   ///< updates board highlight squares (pointlesss setting Player** doing in evry loop - move to init)-  pointer remember pointer ids pointing to.
                                        //TODO(FOTO#1#)think about that code is much less readable when Board have  connection with Engine class, sharing the same pointer - its faster but worth ??, If it's worth make Bpard share current turn pointer
    protected:


    private:
        bool checkWin(int height_index,int width_index,Player* current_turn);      ///checks if just done turn have made current player winnner
        bool squareAction(int height_index, int width_index,Player* currrent_turn);///<action of single square Player** is a pointer to current  players turn from Engine class
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; ///< draws all squares. this is used after all seting what to hilight, mark, ect

        Square** board_array;                                   ///<pointer to dynamic allocated array of squares. deletes  in destructor
        int height;                                             ///<height of the dynamic array of squares
        int width;                                              ///<width of the dynamic array of squares
        sf::Vector2i* mouse;                                    ///< pointer to mouse var from Engine
        sf::Texture texture;                                    ///<basic every single square texture
        bool* clicked;                                          ///< pointer to var witch says if
        Square* mouse_hilighting;                               ///<pointer to square on which mouse is on highlight
};

#endif // BOARD_H