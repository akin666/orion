/*
 * resource.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "resource.hpp"
#include <event/event.hpp>
#include <event/loadingevent.hpp>

#define RESOURCE_STATE_NONE 	0x0000
#define RESOURCE_STATE_BUFFERED	0x0001
#define RESOURCE_STATE_LOADING	0x0002
#define RESOURCE_STATE_REALIZED	0x0004

namespace orion
{

Resource::Resource( const ResourceID& id , string8 path )
: state( RESOURCE_STATE_NONE ),
  id( id ),
  path( path )
{
}

Resource::~Resource()
{
}

void Resource::setBuffered( bool val )
{
	val ? ( state |= RESOURCE_STATE_BUFFERED ) : ( state &= ~RESOURCE_STATE_BUFFERED );
}

void Resource::setLoading( bool val )
{
	val ? ( state |= RESOURCE_STATE_LOADING ) : ( state &= ~RESOURCE_STATE_LOADING );
}

void Resource::setRealized( bool val )
{
	val ? ( state |= RESOURCE_STATE_REALIZED ) : ( state &= ~RESOURCE_STATE_REALIZED );
}

bool Resource::hasBuffered()
{
	return (state & RESOURCE_STATE_BUFFERED) != 0;
}

bool Resource::hasLoading()
{
	return (state & RESOURCE_STATE_LOADING) != 0;
}

bool Resource::hasRealized()
{
	return (state & RESOURCE_STATE_REALIZED) != 0;
}

ResourceID Resource::getID() const
{
	return id;
}

string8 Resource::getPath() const
{
	return path;
}

void Resource::startedLoading()
{
	sendEvent<LoadingEvent>( LoadingEvent( id , LoadingEvent::Started ) );
}

void Resource::loadingSuccess()
{
	sendEvent<LoadingEvent>( LoadingEvent( id , LoadingEvent::Finished ) );
}

void Resource::loadingError()
{
	sendEvent<LoadingEvent>( LoadingEvent( id , LoadingEvent::Error ) );
}

} // namespace orion
