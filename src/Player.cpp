#include "Player.h"

Player::Player(){
}
void Player::setTexture(char *fileDir){
    texture_marked.loadFromFile(fileDir);
}
Player::~Player(){
    DEBUG_MSG("badass Player removing"<<std::endl);
}
sf::Texture* Player::getTexturePtr(){
    return &texture_marked;
}
