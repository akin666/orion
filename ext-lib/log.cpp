/*
 * log.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "log.hpp"
#include <iostream>
#include <native>
#include <stdarg.h>
#include <stdio.h>


#define MAX_LOG_MSG_LEN 2048

Log::Log()
{
}

Log::~Log()
{
}

void Log::printMessage( string8 message )
{
	::orion::message( message.c_str() );
}

void Log::printError( string8 message )
{
	::orion::alert( message.c_str() );
}

void Log::printWarning( string8 message )
{
	::orion::warning( message.c_str() );
}

void Log::message( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	printMessage( string8(buffer) );
}

void Log::error( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	printError( string8(buffer) );
}

void Log::warning( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	printWarning( string8(buffer) );
}

