#include "Board.h"
#include<iostream>
#include <AiPlayer.h>
#include <fstream>
#include <unistd.h>

Board::Board()
        :
        height(0),
        width(0) {
}

Board::Board(int height_in, int width_in) {
    init(height_in, width_in);
}

Board::~Board() {
    DEBUG_MSG("badass Board removing" << std::endl);
}

void Board::init(int height_in, int width_in) {
    width = width_in;
    height = height_in;
    texture->loadFromFile("textures/square_tex.png");
    board_array.resize(height_in);
    for (int height_index = 0; height_index < height_in; height_index++)
        board_array[height_index].resize(width_in);
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            board_array[height_index][width_index].setPosition(width_index * (SQUARE_SIZE + 2) + MOVE_WIDTH,
                                                               height_index * (SQUARE_SIZE + 2) + MOVE_HEIGHT);
            board_array[height_index][width_index].setTexture(texture);
        }
    }
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++)
            target.draw(board_array[height_index][width_index]);
    }
}

sf::Vector2i Board::getBoardPosition(sf::Vector2i mouse_position) {
    sf::Vector2i board_position;
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            if (board_array[height_index][width_index].getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
                board_position.x = height_index;
                board_position.y = width_index;
            }
        }
    }
    return board_position;
}

Board::BoardState Board::update(bool &clicked, Player *currrent_turn, sf::Vector2i &current_mouse_position) {
    static sf::Vector2i last_board_position;
    BoardState state_tmp = NextTurn;
#ifndef NDEBUG
    sf::Vector2i positioner_tmp;
    positioner_tmp.x = 0;
    positioner_tmp.y = 0;
    positioner_tmp = getBoardPosition(current_mouse_position);
    if (positioner_tmp != last_board_position) {
        last_board_position = positioner_tmp;
//        DEBUG_MSG("Position = " << last_board_position.x << "  ,  " << last_board_position.y << std::endl);
    }
#endif
    for (int height_index = 0; height_index < height; height_index++) {
        for (int width_index = 0; width_index < width; width_index++) {
            hilight(height_index, width_index, current_mouse_position);
            if (currrent_turn->isPlayerUsingGui())
                state_tmp = updateField(clicked, height_index, width_index, currrent_turn, current_mouse_position);
            else {
                //TODO this may go bad
                AiPlayer *ai = dynamic_cast<AiPlayer *>(currrent_turn);
                if (ai->inProggres == false) {
                    ai->calcMove(*this);
                    std::cout << "test" << std::endl;
                    usleep(1000000);
                    std::cout << "test" << std::endl;
                }
                if (ai->inProggres == true && ai->isReady == true) {
                    std::ofstream myfile;
                    auto turn = ai->getResult();
                    myfile.open("example.txt");
                    myfile << getBoardData();
                    std::cout << "\nmove: " << turn[0] << " " << turn[1] << std::endl;
                    myfile << ": " << turn[0] << " " << turn[1] << std::endl;
                    myfile.close();
                    makeMove(turn[0], turn[1], currrent_turn);
                    std::cout << "\nnumber of 3: " << count(3, currrent_turn) << std::endl;
                    state_tmp = checkWin(turn[0], turn[1], currrent_turn);
                    getBoardData();
                    return state_tmp;
                } else {
                    state_tmp = WaitingForTurn;
                    return WaitingForTurn;
                }
            }
            if (state_tmp != WaitingForTurn) {// TODO(foto) fixxx
                return state_tmp;
            }
        }
    }

    return
            state_tmp;
}

Board::BoardState Board::updateField(bool clicked, int height_index, int width_index, Player *currrent_turn,
                                     sf::Vector2i &current_mouse_position) {
    if (board_array[height_index][width_index].getGlobalBounds().contains(current_mouse_position.x,
                                                                          current_mouse_position.y)) {
        auto current_square_analiized = &(board_array[height_index][width_index]);
        if (!board_array[height_index][width_index].isMarked())  // marking and hillighting only fr ummarked squares
        {
            if (clicked) {
                makeMove(height_index, width_index, currrent_turn);
                std::cout << "\nnumber of 3: " << count(3, currrent_turn) << std::endl;
                return checkWin(height_index, width_index, currrent_turn);
            }
            return WaitingForTurn;
        }
        return WaitingForTurn;
    }
    return WaitingForTurn;
}

Board::BoardState Board::checkWin(int height_index_of_last_move, int width_index_of_last_move,
                                  Player *currrent_turn) const {
    /////////
    int counter = 1;
    int i = 1;
    assert(currrent_turn != nullptr);
    while (height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        //exit(1);
        return Winner;
    }


    ////////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move + i < WIDTH &&
           board_array[height_index_of_last_move][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        //exit(1);
        return Winner;
    }

    ////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move + i < WIDTH && height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move - i >= 0 && height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }
    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        // exit(1);
        return Winner;
    }

    ////////////////////
    ///////////////////////
    counter = 1;
    i = 1;
    while (width_index_of_last_move - i >= 0 && height_index_of_last_move + i < HEIGHT &&
           board_array[height_index_of_last_move + i][width_index_of_last_move - i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    i = 1;
    while (width_index_of_last_move + i < WIDTH && height_index_of_last_move - i >= 0 &&
           board_array[height_index_of_last_move - i][width_index_of_last_move + i].getMarkedBy() == currrent_turn) {
        counter++;
        i++;
    }

    if (counter >= IN_A_ROW_TO_WIN) {
        DEBUG_MSG("ENDO GEJMO");
        // exit(1);
        return Winner;
    }
    ////////////////////

    return NextTurn;
}

void Board::hilight(int height_index, int width_index, sf::Vector2i &current_mouse_position) {

    if (board_array[height_index][width_index].getGlobalBounds().contains(current_mouse_position.x,
                                                                          current_mouse_position.y)) {
        if (!board_array[height_index][width_index].isMarked())  // marking and hillighting only fr ummarked squares
        {
            auto current_square_to_hilight = &(board_array[height_index][width_index]);
            if (board_array[height_index][width_index].getFillColor() != sf::Color::Yellow)
                current_square_to_hilight->setFillColor(sf::Color::Yellow);
        }
    } else if (board_array[height_index][width_index].getFillColor() != sf::Color::White)
        board_array[height_index][width_index].setFillColor(sf::Color::White);

}

std::string Board::getBoardData() {
    std::string boardDataString;
    for (auto i :board_array) {
        for (auto j :i)
            if (j.marked_by == nullptr)
                boardDataString += '.';
            else
                boardDataString += j.marked_by->player_char;
        boardDataString += '\n';
    }
    boardDataString += '\n';
    return boardDataString;
}

bool Board::makeMove(int hight, int width, Player *player) {
    lastMove = {hight, width};
    board_array[hight][width].mark(player);
    firstMove = false;
    return false;
}

bool Board::isSquareMarked(int move_hight, int move_width) {
    if (board_array[move_hight][move_width].marked_by != nullptr)
        return true;
    return false;
}

bool Board::isMoveInBounds(int move_hight, int move_width) const {
    if (move_hight >= 0 && move_width >= 0 && move_hight < height && move_width < width)
        return true;

    return false;
}

bool Board::isMovePossible(int move_hight, int move_width) {
    if (isMoveInBounds(move_hight, move_width)) {//TODO enkapsulate
        if (!isSquareMarked(move_hight, move_width))
            return true;
    }
    return false;
}

int Board::getHeight() const {
    return height;
}

int Board::getWidth() const {
    return width;
}

bool Board::isItFirstMove() const {
    return firstMove;
}

int Board::countNew(int what, Player *player) {
    int counter = 0;

    for (int height_index = lastMove[0]; height_index < lastMove[0] + 1; height_index++)
        for (int width_index = lastMove[1]; width_index < lastMove[1] + 1; width_index++)
            if (board_array[height_index][width_index].marked_by == player) {
                int lenghtCounterV = 0;
                if (!isMoveInBounds(height_index, width_index - 1) ||
                    board_array[height_index][width_index - 1].marked_by != player) {
                    for (; isMoveInBounds(height_index, width_index + lenghtCounterV) &&
                           board_array[height_index][width_index + lenghtCounterV].marked_by == player;
                           ++lenghtCounterV) {
                    }
                }
                int lenghtCounterH = 0;
                if (!isMoveInBounds(height_index - 1, width_index) ||
                    board_array[height_index - 1][width_index].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterH, width_index) &&
                           board_array[height_index + lenghtCounterH][width_index].marked_by == player;
                           ++lenghtCounterH) {
                    }
                }
                int lenghtCounterULDR = 0;
                if (!isMoveInBounds(height_index - 1, width_index - 1) ||
                    board_array[height_index - 1][width_index - 1].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterULDR, width_index + lenghtCounterULDR) &&
                           board_array[height_index + lenghtCounterULDR][width_index + lenghtCounterULDR].marked_by ==
                           player;
                           ++lenghtCounterULDR) {
                    }
                }
                int lenghtCounterURDL = 0;
                if (!isMoveInBounds(height_index - 1, width_index - 1) ||
                    board_array[height_index - 1][width_index + 1].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterURDL, width_index - lenghtCounterURDL) &&
                           board_array[height_index + lenghtCounterURDL][width_index - lenghtCounterURDL].marked_by ==
                           player;
                           ++lenghtCounterURDL) {
                    }
                }
                if (lenghtCounterH >= what)
                    ++counter;
                if (lenghtCounterV >= what)
                    ++counter;
                if (lenghtCounterULDR >= what)
                    ++counter;
                if (lenghtCounterURDL >= what)
                    ++counter;
            }

    return counter;
}

int Board::count(int what, Player *player) const {
    int counter = 0;

    for (int height_index = 0; height_index < height; height_index++)
        for (int width_index = 0; width_index < width; width_index++)
            if (board_array[height_index][width_index].marked_by == player) {
                int lenghtCounterV = 0;
                if (!isMoveInBounds(height_index, width_index - 1) ||
                    board_array[height_index][width_index - 1].marked_by != player) {
                    for (; isMoveInBounds(height_index, width_index + lenghtCounterV) &&
                           board_array[height_index][width_index + lenghtCounterV].marked_by == player;
                           ++lenghtCounterV) {
                    }
                }
                int lenghtCounterH = 0;
                if (!isMoveInBounds(height_index - 1, width_index) ||
                    board_array[height_index - 1][width_index].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterH, width_index) &&
                           board_array[height_index + lenghtCounterH][width_index].marked_by == player;
                           ++lenghtCounterH) {
                    }
                }
                int lenghtCounterULDR = 0;
                if (!isMoveInBounds(height_index - 1, width_index - 1) ||
                    board_array[height_index - 1][width_index - 1].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterULDR, width_index + lenghtCounterULDR) &&
                           board_array[height_index + lenghtCounterULDR][width_index + lenghtCounterULDR].marked_by ==
                           player;
                           ++lenghtCounterULDR) {
                    }
                }
                int lenghtCounterURDL = 0;
                if (!isMoveInBounds(height_index - 1, width_index - 1) ||
                    board_array[height_index - 1][width_index + 1].marked_by != player) {

                    for (; isMoveInBounds(height_index + lenghtCounterURDL, width_index - lenghtCounterURDL) &&
                           board_array[height_index + lenghtCounterURDL][width_index - lenghtCounterURDL].marked_by ==
                           player;
                           ++lenghtCounterURDL) {
                    }
                }
                if (lenghtCounterH >= what)
                    ++counter;
                if (lenghtCounterV >= what)
                    ++counter;
                if (lenghtCounterULDR >= what)
                    ++counter;
                if (lenghtCounterURDL >= what)
                    ++counter;
            }

    return counter;
}


