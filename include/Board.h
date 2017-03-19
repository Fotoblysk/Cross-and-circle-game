#ifndef BOARD_H
#define BOARD_H

#include "Square.h"

#define IN_A_ROW_TO_WIN 5
#define HEIGHT 20
#define WIDTH 30
#define MOVE_HEIGHT 5
#define MOVE_WIDTH 5

#include<../debugging_tolls.h>

//TODO(FOTO#1#): EXAMPLE5
/*!
 * \brief Board class. Have dynamic array of squares. free memory in destructor .checks if someone won. hilight current square.
*/
class Board : public sf::Drawable, sf::Transformable {
public:
    enum BoardState {
        WaitingForTurn, NextTurn, Winner
    };

    Board();                                                ///<pointers to nullptr . vars to  0. Board useless until  initialized with init(...)
    Board(int height_in, int width_in,
          sf::Vector2i &mouse_in); ///< inits board sets size and  mouse var allocates dynamic array of squares (runs init function).
    virtual ~Board();

    void init(int height_in, int width_in, sf::Vector2i &mouse_in); ///< inits board sets size and  mouse var

    BoardState update(bool &marked_in, Player *currrent_turn,
                      sf::Vector2i &current_mouse_position);   ///< updates board highlight squares
    sf::Vector2i getBoardPosition(sf::Vector2i mouse_position);

protected:

private:
    BoardState checkWin(int height_index, int width_index,
                        Player *current_turn) const;      ///checks if just done turn have made current player winnner
    BoardState squareAction(bool &clicked, int height_index, int width_index, Player *currrent_turn,
                            sf::Vector2i &current_mouse_position);///<action of single square Player* is a pointer to current  players turn from Engine class
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const; ///< draws all squares. this is used after all seting what to hilight, mark, ect
    Square **board_array;                                   ///<pointer to dynamic allocated array of squares. deletes  in destructor
    int height;                                             ///<height of the dynamic array of squares
    int width;                                              ///<width of the dynamic array of squares
    sf::Texture texture;                                    ///<basic every single square texture
    Square *mouse_hilighting;                               ///<pointer to square on which mouse is on highlight
    BoardState state;
    sf::Vector2i current_board_position;
};

#endif // BOARD_H
