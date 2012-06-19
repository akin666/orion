/*
 * time.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef TIME_HPP_
#define TIME_HPP_

#include "common.hpp"

namespace orion {

class Time
{
public:
	Second s;
	MicroSecond us;

	Time()
	: s(0),us(0) {}
	Time( const Time& o )
	: s(o.s),us(o.us) {}
};

} // orion

#endif // TIME_HPP_
