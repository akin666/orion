/*
 * random.cpp
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#include "random.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace orion {

Random::Random()
{
	srand( time(NULL) );
}

Random::~Random() {
}

float Random::getFloat()
{
	// returns 32bit integer, change into float directly. should be random. TRULY
	// [0.0f,1.0f]
	return rand()/(RAND_MAX+1.f);
}

unsigned char Random::getUChar()
{
	return (unsigned char)(getFloat()*0xFF);
}

char Random::getChar()
{
	return (char)(getFloat()*0xFF);
}

int Random::getInt()
{
	return rand();
}

}
