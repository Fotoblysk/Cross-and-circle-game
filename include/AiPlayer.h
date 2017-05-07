#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <atomic>
#include <thread>

class Board; //FIXME this is baaad
class AiPlayer : public Player {
public:
    enum Strategy {//TODO change this to strategy design pattern
        Random,
        Random2,
        MinMax,
        Neural
    };

    AiPlayer(Strategy strategy_in, Player* otherPlayer_in);


    std::array<int, 2> calculated_move = {{0, 0}};
    std::atomic_bool isReady{true};

    bool isPlayerUsingGui() override;

    bool inProggres = false;

    std::array<int, 2> getResult();

    virtual ~AiPlayer();

    void calcMove(Board board);

    std::thread myThread;
protected:

private:
    Strategy strategy;

    void randomMove(Board boardCopy);


    void minMaxMove(Board boardCopy, unsigned int depth);

    void randomMove2(Board boardCopy);


    bool isMoveClinging(Board &board, std::array<int,2> &move);
    Player* otherPlayer = nullptr;
public:
    void setOtherPlayer(Player *otherPlayer);

private:


    long long int getScore(Board &boardCopy, unsigned int depth, Player *player);

};

#endif // AIPLAYER_H
