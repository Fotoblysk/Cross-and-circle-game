#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <atomic>
#include <thread>

class Board; //FIXME this is baaad
class AiPlayer : public Player {
public:
    AiPlayer();

    void clacRandomMove(Board &board);

    std::vector<int> calculated_move{0, 0};
    std::atomic_bool isReady{true};

    bool isPlayerUsingGui() override;

    bool inProggres = false;

    std::vector<int> getResult();

    virtual ~AiPlayer();

protected:

private:
    std::thread myThread;

    void randomMove(Board boardCopy);
};

#endif // AIPLAYER_H
