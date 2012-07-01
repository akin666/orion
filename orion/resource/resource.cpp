/*
 * resource.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "resource.hpp"

namespace orion
{

Resource::Resource()
: state( None )
{
}

Resource::~Resource()
{
}

void Resource::setLoaded( bool val )
{
	if( val )
	{
		state |= Loaded;
	}
	else
	{
		state &= ~Loaded;
	}
}

void Resource::setBuffered( bool val )
{
	if( val )
	{
		state |= Buffered;
	}
	else
	{
		state &= ~Buffered;
	}
}

bool Resource::loaded()
{
	return (state & Loaded) != 0;
}

bool Resource::buffered()
{
	return (state & Buffered) != 0;
}

} // namespace orion
