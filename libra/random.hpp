/*
 * random.h
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#ifndef ORION_RANDOM_H_
#define ORION_RANDOM_H_

namespace orion {

class Random
{
public:
	Random();
	virtual ~Random();

	float getFloat();
	unsigned char getUChar();
	char getChar();
	int getInt();
};

} // orion

#endif // RANDOM_H_
