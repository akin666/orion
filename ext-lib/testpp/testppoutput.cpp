/*
 * testppoutput.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#include "testppoutput.hpp"

namespace testpp
{

Output::Output()
{
}

Output::~Output()
{
}

bool Output::eval( int number , const std::string& module , Test::Success success , const std::string& str )
{
	return true;
}

} // namespace testpp
