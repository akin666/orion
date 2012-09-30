/*
 * common.cpp
 *
 *  Created on: 16.7.2012
 *      Author: akin
 */

#include "common.hpp"
#include <utf8>
#include <cstdlib>
#include <ctime>

namespace orion {

void convertText( string8& input, string32& add )
{
	utf8::unchecked::utf8to32( input.begin() , input.end() , back_inserter(add));
}

void convertText( string32& input, string8& add )
{
	utf8::unchecked::utf32to8( input.begin() , input.end() , back_inserter(add));
}

void initCommon()
{
	srand( time(NULL) ); // init random.
}

} // namespace orion

