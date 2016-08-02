#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"


class HumanPlayer:public Player
{
    public:
        HumanPlayer(){move_premission = true;}
        virtual ~HumanPlayer();

    protected:

    private:
};

#endif // HUMANPLAYER_H
