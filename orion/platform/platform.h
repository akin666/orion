/*
 * platform.h
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <orion>

#define COMMON_PLATFORM

namespace orion {

// Logging..
void message( const char *message );
void warning( const char *message );
void alert( const char *message );

// Time
void getTime( Time& time );
Time getTime( Year year, Month month, Day day, Hour hour, Minute minute, Second second, MicroSecond ms );
Timezone getTimezone( );
Year getYear( const Time& time );
Day getDayOfYear( const Time& time );
Day getDayOfMonth( const Time& time );
Hour getHour( const Time& time );
Minute getMinute( const Time& time );
Month getMonth( const Time& time );
Second getSecond( const Time& time );
MilliSecond getMilliSecond( const Time& time );
MicroSecond getMicroSecond( const Time& time );
Time parseTime( std::string str );
std::string timeToString( const Time& time );

} // orion

#endif /* PLATFORM_H_ */
