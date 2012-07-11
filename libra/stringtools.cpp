/*
 * stringtools.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "stringtools"
#include <functional>
#include <algorithm>
#include <orion>

namespace orion {
namespace stringtools {

void toUpper( string8& str )
{
	std::transform(str.begin(), str.end(), str.begin(), toupper );
}

void toLower( string8& str )
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

template<>
string8 to_ot<string8, string8>( const string8 from )
{
	return from;
}

template<>
bool to_ot<bool, string8>( const string8 from )
{
	return from.size() == 4; // true == 4 false == 5
}

template<>
string8 to_ot<string8, bool>( const bool from )
{
	return from ? "true" : "false";
}

} // stringtools
} // orion
