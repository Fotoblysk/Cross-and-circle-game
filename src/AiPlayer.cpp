#include <Board.h>
#include "AiPlayer.h"
#include <random>
#include <thread>

AiPlayer::AiPlayer() {
    //ctor
}

AiPlayer::~AiPlayer() {
    //dtor
}

bool AiPlayer::isPlayerUsingGui() {
    return false;
}

void AiPlayer::randomMove(Board boardCopy) {//TODO change to std::future
    std::cout << "dupa in t" << std::endl;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> dist_w(0, boardCopy.getWidth());
    std::uniform_int_distribution<int> dist_h(0, boardCopy.getHeight());
    calculated_move = {0, 0};
    bool isOk;
    do {
        calculated_move = {dist_h(eng), dist_w(eng)};
        isOk = boardCopy.isMovePossible(calculated_move[0], calculated_move[1]);
    } while (isOk != true);
    isReady = true;
}

std::vector<int> AiPlayer::getResult() {
    assert(isReady);
    inProggres = false;
    myThread.join();
    return calculated_move;
}

void AiPlayer::clacRandomMove(Board &board) {
    assert(isReady);
    inProggres = true;
    isReady = false;
    std::cout << "dupa in t" << std::endl;
    myThread = std::thread(&AiPlayer::randomMove, this, board);
}
