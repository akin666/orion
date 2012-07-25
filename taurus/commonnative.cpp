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
#include <TGAImage.h>

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
// Precise UTC Time
void getTime( Time& time )
{
	// TODO!
	timeval tmp;
	gettimeofday( &tmp , NULL );

	time.us = tmp.tv_usec + (tmp.tv_sec * S_TO_US);
}

// Local Time
void getTime( LocalTime& time )
{
	time_t rawtime;
	struct tm * info;
	::time ( &rawtime );
	info = localtime ( &rawtime );

	time.setYear( info->tm_year + 1900 );
	time.setMonth( info->tm_mon + 1 );
	time.setDay( info->tm_mday );
	time.setHour( info->tm_hour );
	time.setMinute( info->tm_min );
	time.setSecond( info->tm_sec );
	time.setWeekday( info->tm_wday + 1 );
	time.setDayOfYear( info->tm_yday + 1 );
	time.setTimezone( 666 );
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
	glm::ivec2 resolution;
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
	switch( softimage.getMode() )
	{
	case RGBA8 :
		return imagesaver::RGBA8write( path + ".tga" , softimage.getResolution().x , softimage.getResolution().y , softimage.access() );
	case RGB8 :
		return imagesaver::RGB8write( path + ".tga" , softimage.getResolution().x , softimage.getResolution().y , softimage.access() );
	case ALPHA8 	:
	case LUMINANCE 	:
	case INTENSITY 	:
		return imagesaver::ALPHA8write( path + ".tga" , softimage.getResolution().x , softimage.getResolution().y , softimage.access() );
	default :
		break;
	}
	return false;
}

} // orion

#endif // USE_COMMON_NATIVE

