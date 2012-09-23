/*
 * testppoutput.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#include "testppoutput.hpp"
#include <iostream>

namespace testpp
{

Output::Output()
{
}

Output::~Output()
{
}

bool Output::eval( Test *test )
{
	if( test == NULL )
	{
		std::cerr << "Test pointer was NULL" << std::endl;
		return false;
	}

	if( test->init() )
	{
		if( test->run() )
		{
			if( !test->clean() )
			{
				std::cerr << "Test " << test->getName() << "failed at clean." << std::endl;
			}
		}
		else
		{
			std::cerr << "Test " << test->getName() << "failed at run." << std::endl;
		}
	}
	else
	{
		std::cerr << "Test " << test->getName() << "failed at init." << std::endl;
	}

	// if anything else than OK is in bits, print something
	if( (test->success() & ~Test::OK) != 0x0 )
	{
		std::cerr << "Test " << test->getName() << ": " << test->logMessage() << std::endl;
	}

	// if success is 'OK' then we still continue.
	return (test->success() & Test::OK) != 0x0;
}

} // namespace testpp
