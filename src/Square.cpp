#include "Square.h"
#include<iostream>
Square::Square()
    :
    texture(NULL)
{
    marked_by= NULL;
    square.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    square.setPosition(sf::Vector2f(0, 0));
    if(texture)
        square.setTexture(texture);
    square.setFillColor(sf::Color::White);
}
void Square::setPosition(float x, float y){
    square.setPosition(sf::Vector2f(x, y));
}
Square::~Square(){
    DEBUG_MSG("badass square rm ");
    //dtor
}
void Square::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	states.transform *= getTransform();
 	target.draw(square);
}
void Square::mark(Player *player_ptr){
    DEBUG_MSG("marked"<<std::endl);
    marked_by=player_ptr;
    setTexture(marked_by->getTexturePtr());
}

void Square::setTexture(sf::Texture *texture_in){
    texture=texture_in;
    if(texture)
        square.setTexture(texture);
}
bool Square::isMarked() const{
    if(marked_by)
        return true;
    return false;
}
Player* Square::getMarkedBy() const{
    return marked_by;
}
