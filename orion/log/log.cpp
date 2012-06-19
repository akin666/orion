/*
 * log.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "log.hpp"
#include <iostream>
#include <platform/platform.h>
#include <stdarg.h>
#include <stdio.h>


#define MAX_LOG_MSG_LEN 2048

namespace orion {

Log::Log()
{
}

Log::~Log()
{
}

void Log::printMessage( std::string message )
{
	::orion::message( message.c_str() );
}

void Log::printError( std::string message )
{
	::orion::alert( message.c_str() );
}

void Log::printWarning( std::string message )
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
	printMessage( std::string(buffer) );
}

void Log::error( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	printError( std::string(buffer) );
}

void Log::warning( const char* format , ... )
{
	char buffer[ MAX_LOG_MSG_LEN];
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, (MAX_LOG_MSG_LEN - 1), format, args);
	va_end( args );
	printWarning( std::string(buffer) );
}

} // namespace orion
