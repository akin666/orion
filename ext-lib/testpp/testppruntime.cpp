/*
 * testppruntime.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#include "testppruntime.hpp"

namespace testpp
{

Runtime::Runtime( Output& output )
: output( output )
{
}

Runtime::~Runtime()
{
}

void Runtime::clear()
{
	tests.clear();
}

void Runtime::run()
{
	bool critical_fail = false;
	int number = 0;
	for( TestSet::iterator iter = tests.begin() ; iter != tests.end() ; ++iter )
	{
		++number;
		if( !(*iter)->init() )
		{
			critical_fail = true;
			break;
		}
		if( !(*iter)->run() )
		{
			critical_fail = true;
			break;
		}
		if( !(*iter)->clean() )
		{
			critical_fail = true;
			break;
		}

		// Measure success..
		// And possibly Log it.
		if( !output.eval( number , (*iter)->getName() , (*iter)->success() , (*iter)->logMessage() ) )
		{
			break;
		}
	}
}

} // namespace testpp
