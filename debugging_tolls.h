//#define NDEBUG
#include<assert.h>
#ifndef NDEBUG
    #define DEBUG_MSG(str) do { std::cout << str;} while( false )
#else
    #define DEBUG_MSG(str) ((void)0)
#endif
