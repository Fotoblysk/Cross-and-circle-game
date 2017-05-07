#include <Board.h>
#include "AiPlayer.h"
#include <random>
#include <thread>
#include <climits>
#include <iostream>
#include <future>

AiPlayer::AiPlayer(Strategy strategy_in, Player *otherPlayer_in) {
    strategy = strategy_in;
    otherPlayer = otherPlayer_in;
}

AiPlayer::~AiPlayer() {
    myThread.detach();
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

bool AiPlayer::isMoveClinging(Board &board, std::array<int, 2> &move) {//TODO change to std::future
    for (auto i = move[0] - 1; i < move[0] + 2; ++i)
        for (auto j = move[1] - 1; j < move[1] + 2; ++j)
            if (board.isMoveInBounds(i, j) &&
                board.isSquareMarked(i, j)) {
                return true;
            }
    return false;
}

long long AiPlayer::getScore(Board &boardCopy, unsigned int depth, Player *player) {
    std::vector<std::array<int, 2>> possibleMoves;
    std::array<int, 2> calculated_move;
    bool isOk = false;
    long long score = 0;


    if (depth > 0) {
        if (!boardCopy.isItFirstMove()) {
            int j = 0;
            for (int i = 0; i < boardCopy.getHeight() && isOk != true; ++i)
                for (j = 0; j < boardCopy.getWidth() && isOk != true; ++j) {
                    calculated_move = {i, j};
                    if (boardCopy.isMovePossible(i, j) && isMoveClinging(boardCopy, calculated_move)) {
                        possibleMoves.push_back(calculated_move);
                    }
                }
        }
        score = 12000 * (boardCopy.count(5, this) - boardCopy.count(5, otherPlayer));
        if (score == 0) {
            for (auto &&i :possibleMoves) {
                auto boardTmp = boardCopy;
                boardTmp.makeMove(i[0], i[1], player);
                if (player == this)
                    score += (getScore(boardTmp, depth - 1, otherPlayer));
                else
                    score += (getScore(boardTmp, depth - 1, this));
            }
            long long newscore = score / possibleMoves.size();
            if (newscore == 0)
                if (score > 0)
                    score = 1;
                else if (score < 0)
                    score = -1;
                else
                    score = newscore;
        } else {
        }


    } else {
        score = (10000 * boardCopy.count(5, this) + 100 * boardCopy.count(4, this) +
                 boardCopy.count(3, this)
                 - (10000 * boardCopy.count(5, otherPlayer) + 100 * boardCopy.count(4, otherPlayer) +
                    boardCopy.count(3, otherPlayer)));
    }
    return score;
}

void AiPlayer::minMaxMove(Board boardCopy, unsigned int depth) {//TODO change to std::future
    calculated_move = {0, 0};
    std::vector<std::array<int, 2>> possibleMoves;
    unsigned short int threadNumber = std::thread::hardware_concurrency();
    std::vector<std::thread> tArray;
    tArray.resize(threadNumber);
    bool isOk = false;
    if (!boardCopy.isItFirstMove()) {
        int j = 0;
        for (int i = 0; i < boardCopy.getHeight() && isOk != true; ++i)
            for (j = 0; j < boardCopy.getWidth() && isOk != true; ++j) {
                calculated_move = {i, j};
                if (boardCopy.isMovePossible(i, j) && isMoveClinging(boardCopy, calculated_move)) {
                    possibleMoves.push_back(calculated_move);
                }
            }

        long long bestScore = LLONG_MIN;
        for (auto &i :possibleMoves) {
            auto boardTmp = boardCopy;
            boardTmp.makeMove(i[0], i[1], this);
            int score = getScore(boardTmp, depth - 1, otherPlayer);
            std::cout << "sum : " << i[0] << " " << i[1] << " " << score << std::endl;
            if (score >= bestScore) {
                bestScore = score;
                calculated_move = i;
            }
        }
        isReady = true;
    } else
        randomMove(boardCopy);
}

void AiPlayer::randomMove2(Board boardCopy) {//TODO change to std::future
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> dist_w(0, boardCopy.getWidth());
    std::uniform_int_distribution<int> dist_h(0, boardCopy.getHeight());
    calculated_move = {0, 0};
    bool isOk;
    do {
        calculated_move = {dist_h(eng), dist_w(eng)};
        isOk = boardCopy.isMovePossible(calculated_move[0], calculated_move[1]);
        if (isOk && !boardCopy.isItFirstMove()) {
            isOk = isMoveClinging(boardCopy, calculated_move);
        }
    } while (isOk != true);
    isReady = true;
}


std::array<int, 2> AiPlayer::getResult() {
    assert(isReady);
    inProggres = false;
    if (myThread.joinable())
        myThread.join();
    return calculated_move;
}

void AiPlayer::calcMove(Board board) {
    assert(isReady);
    inProggres = true;
    isReady = false;
    std::cout << "deb2" << std::endl;
    switch (strategy) { //TODO change to strategy design pattern
        case Strategy::Random:
            myThread = std::thread(&AiPlayer::randomMove, this, board);
            break;
        case Strategy::Random2:
            myThread = std::thread(&AiPlayer::randomMove2, this, board);
            break;
        case Strategy::MinMax:
            myThread = std::thread(&AiPlayer::minMaxMove, this, board, 4);
            //if (myThread.joinable())
            //    myThread.join();
            break;
        default:
            myThread = std::thread(&AiPlayer::randomMove, this, board);
    }
}

void AiPlayer::setOtherPlayer(Player *otherPlayer) {
    AiPlayer::otherPlayer = otherPlayer;
}

