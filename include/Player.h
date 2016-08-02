#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<SFML/Graphics.hpp>
#include<../debugging_tolls.h>
#include<string>
/*!
 * \brief Player class - pointers to player have a lot of usage in program.
 * All Squares have pointer to player which  were marked by
 * pointers to players are also used by Engine class to set whose turn is now.
*/
class Player
{
    public:
        Player(); ///< empty constructor
        virtual ~Player(); ///< empty destructor only msg
        void setTexture(char* fileDir); ///< function setting player texture (initialization staff)
        sf::Texture* getTexturePtr(); ///<returns pointer to current player texture (texture_marked)
        std::string& toStr();
        void setName(std::string);
        virtual bool getMovePremission(){return move_premission;}
        bool move_premission;
    protected:
        int player_number;
        std::string name;
        sf::Texture texture_marked; ///< texture to draw when a player marked square.
        //TODO(FOTO#5#): set default texture to be copied from default square texture,  or gonna make that const , get  deafult from square when creating and print circle crosss square on it before creating a player



};

#endif // PLAYER_H
