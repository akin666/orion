/*
 * log.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef LOG_HPP_
#define LOG_HPP_

#include <common/common.hpp>

namespace orion {

class Log {
public:
	Log();
	virtual ~Log();

	virtual void printMessage( string8 message );
	virtual void printError( string8 message );
	virtual void printWarning( string8 message );

	void message( const char* format , ... );
	void error( const char* format , ... );
	void warning( const char* format , ... );
};

// LOG->message("Hey");
// LOG->error("WTF IS GOING ON? %i" , 666 );
#define LOG createGlobal<Log>()

} // namespace orion
#endif // LOG_HPP_
