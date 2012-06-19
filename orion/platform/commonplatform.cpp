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

	time.s = tmp.tv_sec;
	time.us = tmp.tv_usec;
}

Time getTime( Year year, Month month, Day day, Hour hour, Minute minute, Second second, MicroSecond ms )
{
	Time time;
	timeval tmp;
	gettimeofday( &tmp , NULL );

	time.s = tmp.tv_sec;
	time.us = tmp.tv_usec;

	return time;
}

Timezone getTimezone( )
{
	return 0;
}

Year getYear( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_year + 1900;
}

Day getDayOfYear( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_yday;
}

Day getDayOfMonth( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_mday;
}

Hour getHour( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_hour;
}

Minute getMinute( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_min;
}

Month getMonth( const Time& time )
{
	time_t rawtime = time.s;
	struct tm * info;
	info = localtime ( &rawtime );

	return info->tm_mon + 1; // 0-11??? jeez dudes..
}

Second getSecond( const Time& time )
{
	return time.s % 60;
}

MilliSecond getMilliSecond( const Time& time )
{
	return (MilliSecond)(time.us * 0.001);
}

MicroSecond getMicroSecond( const Time& time )
{
	return time.us;
}

Time parseTime( std::string string )
{
	Time time;
	return time;
}

std::string timeToString( const Time& time )
{
	return "";
}

} // orion

#endif

