#define NDEBUG
/*! \file debugging_tolls.h
 *
 * \brief Personal debug macros. Include after defining NDEBUG to turn off.
 *
 * \author  Fotoblysk ; page: https://github.com/Fotoblysk
 *
 * Contact: fotoblysk@fejm.pl
 *
 * \date  2016/03/18 12:00
*/
#include<assert.h>
#include<iostream>
#ifndef NDEBUG
    #define DEBUG_MSG(str) do { std::cout << str;} while( false )
#else
    #define DEBUG_MSG(str) ((void)0)
#endif
