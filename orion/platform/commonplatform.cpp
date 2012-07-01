/*
 * commonplatform.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "platform.h"

#ifdef COMMON_PLATFORM

#include <iostream>
#include <sys/time.h>

namespace orion {

void message( const char *message )
{
	std::cout << message << std::endl;
}

void warning( const char *message )
{
	std::cout << "Warning! " << message << std::endl;
}

void alert( const char *message )
{
	std::cout << "Error!!! " << message << std::endl;
}


// Time
void getTime( Time& time )
{
	timeval tmp;
	gettimeofday( &tmp , NULL );

	time.us = tmp.tv_usec + (tmp.tv_sec * S_TO_US);
}

Time getTime( Year year, Month month, Day day, Hour hour, Minute minute, Second second, MicroSecond ms )
{
	Time time;
	timeval tmp;
	gettimeofday( &tmp , NULL );

	time.us = tmp.tv_usec + (tmp.tv_sec * S_TO_US);

	return time;
}

Timezone getTimezone( )
{
	return 0;
}

Year getYear( const Time& time )
{
	// [0,xxx] humans use [0,xxx]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_year + 1900;
}

Day getDayOfYear( const Time& time )
{
	// [1,xxx] humans use [1,xxx]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_yday;
}

Day getDayOfMonth( const Time& time )
{
	// [1,xx] humans use [1,xx]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_mday;
}

Hour getHour( const Time& time )
{
	// [0,23] humans use [0,23]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_hour;
}

Minute getMinute( const Time& time )
{
	// [0,59] humans use [0,59]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_min;
}

Month getMonth( const Time& time )
{
	// [0,11] humans use [1,12]
	time_t rawtime = time.us * US_TO_S;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_mon + 1; // 0-11??? jeez dudes, did you drink too much when you designed this api...
}

Second getSecond( const Time& time )
{
	// [0,59] humans use [0,59]
	return ((Second)(time.us  * US_TO_S)) % 60;
}

MilliSecond getMilliSecond( const Time& time )
{
	return (MilliSecond)(time.us * US_TO_MS);
}

MicroSecond getMicroSecond( const Time& time )
{
	return time.us;
}

Time parseTime( std::string str )
{
	// TODO!
	Time time;
	return time;
}

std::string timeToString( const Time& time )
{
	// TODO!
	return "";
}

// Platform tick queries
// (for query joystick, mouse, keyboard, if you have to)
void platformQuery()
{
}

} // orion

#endif

