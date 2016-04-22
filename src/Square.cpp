#include "Square.h"
#include<iostream>

Square::Square()
:
    texture(nullptr),
    marked_by(nullptr)
{
    setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    setPosition(sf::Vector2f(0, 0));
    if(texture)
        setTexture(texture);
    setFillColor(sf::Color::White);
}

Square::~Square(){
    DEBUG_MSG("badass square rm ");
    //dtor
}

void Square::mark(Player *player_ptr){
    DEBUG_MSG("marked" << std::endl);
    marked_by = player_ptr;
    setTexture(marked_by->getTexturePtr());
}

bool Square::isMarked() const{
    if(marked_by)
        return true;
    return false;
}

Player* Square::getMarkedBy() const{
    return marked_by;
}
