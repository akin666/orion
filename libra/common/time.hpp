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
	PreciseTime us;

	Time()
	: us(0) {}
	Time( const Time& o )
	: us(o.us) {}

	FloatTime toFloatTime()
	{
		return us * US_TO_S;
	}

	Time& operator = ( const FloatTime& val )
	{
		// TODO! research what are the losses with this conversion.
		// and at what levels the losses begin to show (days, years, millenia?)
		us = (PreciseTime)(val * S_TO_US);
		return *this;
	}

	operator FloatTime()
	{
		return us * US_TO_S;
	}

	operator PreciseTime()
	{
		return us;
	}
};

} // orion

#endif // TIME_HPP_
