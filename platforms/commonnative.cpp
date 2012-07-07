/*
 * commonnative.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include <native>

#ifdef USE_COMMON_NATIVE

#include <iostream>
#include <sys/time.h>
#include <cstdio>

#ifndef MAX_TEXT_FILE_SIZE
# define MAX_TEXT_FILE_SIZE 1048576
#endif

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


// File I/O
FILE *openFileRead( std::string path )
{
	return fopen ( path.c_str() , "rb" );
}

FILE *openFileWrite( std::string path )
{
	return fopen ( path.c_str() , "wb" );
}

void closeFile( FILE *file )
{
	fclose( file );
}

bool readFile( std::string path , std::string& content )
{
	FILE * file = openFileRead( path );

	if( file == NULL )
	{
		return false;
	}

	int64 size;
	int8 *buffer;

	fseek( file , 0L , SEEK_END);
	size = ftell( file );
	rewind( file );

	if( size > MAX_TEXT_FILE_SIZE )
	{
		closeFile( file );
		return false;
	}

	buffer = new int8[size + 1];

	if( buffer == NULL )
	{
		closeFile( file );
		return false;
	}

	if( fread( buffer , size, 1 , file ) != 1 )
	{
		delete[] buffer;
		closeFile( file );
		return false;
	}
	closeFile( file );

	content = (char*)buffer;

	delete[] buffer;

	return true;
}

} // orion

#endif // USE_COMMON_NATIVE

