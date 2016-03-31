#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<SFML/Graphics.hpp>

//#define NDEBUG
#ifndef NDEBUG
    #define DEBUG_MSG(str) do { std::cout << str;} while( false )
#else
    #define DEBUG_MSG(str) ((void)0)
#endif

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
    protected:

    private:
    sf::Texture texture_marked; ///< texture to draw when a player marked square.
    //TODO(FOTO#5#): set default texture to be copied from default square texture,  or gonna make that const , get  deafult from square when creating and print circle crosss square on it before creating a player



};

#endif // PLAYER_H
