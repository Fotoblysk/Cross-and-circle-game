#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"

class AiPlayer : public Player {
public:
    AiPlayer();
    std::vector<int> getRandomMove();

    virtual ~AiPlayer();

protected:

private:
};

#endif // AIPLAYER_H
