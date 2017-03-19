#ifndef NETWORKENGINE_H
#define NETWORKENGINE_H

#include <Engine.h>


class NetworkEngine : public Engine {
public:
    NetworkEngine();

    virtual ~NetworkEngine();

    //virtual void init(sf::RenderWindow& window)override;            ///<initialization of Engine, sets player textures
    virtual void update(sf::RenderWindow &window) override;          ///updates physics of the game,  draws board.
protected:

private:
};

#endif // NETWORKENGINE_H
