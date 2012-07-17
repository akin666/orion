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

#include <stb_image.h>

#ifndef MAX_TEXT_FILE_SIZE
# define MAX_TEXT_FILE_SIZE 1048576 // 1Megs
#endif

#ifndef MAX_IMAGE_FILE_SIZE
# define MAX_IMAGE_FILE_SIZE 33554432 // 32Megs
#endif

#ifndef MAX_IMAGE_RESOLUTION
# define MAX_IMAGE_RESOLUTION 8192 // So, max to be 8192*8192 ~ 268,435,456 bytes, 268Mb, thats quite alot..
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
void getUTCTime( Time& time )
{
	// TODO!
	getTime( time );
}

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

Time parseTime( string8 str )
{
	// TODO!
	Time time;
	return time;
}

string8 timeToString( const Time& time )
{
	// TODO!
	return "";
}


// File I/O
FILE *openFileRead( string8 path )
{
	return fopen ( path.c_str() , "rb" );
}

FILE *openFileWrite( string8 path )
{
	return fopen ( path.c_str() , "wb" );
}

void closeFile( FILE *file )
{
	fclose( file );
}

bool readFile( string8 path , string8& content )
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

// Image loading functionality _always_ happens through softimage
bool loadImageFile( std::string path , simg::Buffer& softimage )
{
	// define MAX_IMAGE_FILE_SIZE 33554432
	// define MAX_IMAGE_RESOLUTION 8192
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

	if( size > MAX_IMAGE_FILE_SIZE )
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

	// Load image..
	int len;
	glm::ivec2 resolution;
	int *comp;
	int req_comp = 4; // req RGBA

	stbi_uc *data = stbi_load_from_memory( (stbi_uc *)buffer , size , &resolution.x, &resolution.y, &req_comp , req_comp );

	// free filedata buffer.
	delete[] buffer;

	if( resolution.x > MAX_IMAGE_RESOLUTION || resolution.y > MAX_IMAGE_RESOLUTION || req_comp < 1 || req_comp > 4 )
	{
		stbi_image_free( data );
		LOG->error("%s @%i MAX_IMAGE tests failed!" , __FUNCTION__ , __LINE__ );
		return false;
	}

	switch( req_comp )
	{
		case 1 : softimage.setMode( ALPHA8 ); break;
		case 3 : softimage.setMode( RGB8 ); break;
		case 4 : softimage.setMode( RGBA8 ); break;
		default:
		{
			// error..
			LOG->error("%s @%i req_comp tests failed! %i count." , __FUNCTION__ , __LINE__ , req_comp );
			stbi_image_free( data );
			return false;
		}
	}

	softimage.setResolution( resolution );
	if( !softimage.initialize() )
	{
		LOG->error("%s @%i softimage.initialize failed!" , __FUNCTION__ , __LINE__ );
		stbi_image_free( data );
		return false;
	}
	if( !softimage.drawRect( glm::ivec2(0,0) , resolution , data ) )
	{
		LOG->error("%s @%i softimage.drawRect failed!" , __FUNCTION__ , __LINE__ );
		stbi_image_free( data );
		return false;
	}

	// free imagedata
	stbi_image_free( data );
	return true;
}

bool saveImageFile( std::string path , simg::Buffer& softimage )
{
}

} // orion

#endif // USE_COMMON_NATIVE

