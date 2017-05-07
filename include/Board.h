#ifndef BOARD_H
#define BOARD_H

#include "Square.h"

#define IN_A_ROW_TO_WIN 5
#define MOVE_HEIGHT 5
#define MOVE_WIDTH 5

#define HEIGHT 10
#define WIDTH 10

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
    Board(int height_in,
          int width_in); ///< ints board sets size and  mouse var allocates dynamic array of squares (runs init function).
    virtual ~Board();

    void init(int height_in, int width_in); ///< inits board sets size and  mouse var
    bool isMovePossible(int move_hight, int move_width);

    BoardState update(bool &marked_in, Player *currrent_turn,
                      sf::Vector2i &current_mouse_position);   ///< updates board highlight squares
    sf::Vector2i getBoardPosition(sf::Vector2i mouse_position);

    std::string getBoardData();

    bool makeMove(int hight, int width, Player *current_player);

    Player *player1 = nullptr;
    Player *player2 = nullptr;
    std::array<int, 2> lastMove{{0, 0}};

protected:

private:
    BoardState checkWin(int height_index_of_last_move, int width_index_of_last_move,
                        Player *current_turn) const;      ///checks if just done turn have made current player winnner
    BoardState updateField(bool clicked, int height_index, int width_index, Player *currrent_turn,
                           sf::Vector2i &current_mouse_position);///<action of single square Player* is a pointer to current  players turn from Engine class
    void hilight(int height_index, int width_index,
                 sf::Vector2i &current_mouse_position);      ///checks if just done turn have made current player winnner
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const; ///< draws all squares. this is used after all seting what to hilight, mark, ect
    std::vector<std::vector<Square>> board_array;                                   ///<pointer to dynamic allocated array of squares. deletes  in destructor
    int height;
public:
    int getHeight() const;

    int getWidth() const;

    bool isMoveInBounds(int move_hight, int move_width) const;

    bool isSquareMarked(int move_hight, int move_width);

    bool isItFirstMove() const;

    int count(int what, Player *player) const;

    int countNew(int what, Player *player);

private:
    ///<height of the dynamic array of squares
    int width;                                              ///<width of the dynamic array of squares
    bool firstMove = true;
    sf::Texture *texture = new sf::Texture;//FIXME memory leaks!!!                                    ///<basic every single square texture
};

#endif // BOARD_H
