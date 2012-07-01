/*
 * resource.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "resource.hpp"

#define RESOURCE_STATE_NONE 	0x0000
#define RESOURCE_STATE_BUFFERED	0x0001
#define RESOURCE_STATE_LOADED	0x0002

namespace orion
{

Resource::Resource()
: state( RESOURCE_STATE_NONE )
{
}

Resource::~Resource()
{
}

void Resource::setLoaded( bool val )
{
	if( val )
	{
		state |= RESOURCE_STATE_LOADED;
	}
	else
	{
		state &= ~RESOURCE_STATE_LOADED;
	}
}

void Resource::setBuffered( bool val )
{
	if( val )
	{
		state |= RESOURCE_STATE_BUFFERED;
	}
	else
	{
		state &= ~RESOURCE_STATE_BUFFERED;
	}
}

bool Resource::loaded()
{
	return (state & RESOURCE_STATE_LOADED) != 0;
}

bool Resource::buffered()
{
	return (state & RESOURCE_STATE_BUFFERED) != 0;
}

} // namespace orion
