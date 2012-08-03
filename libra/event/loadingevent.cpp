/*
 * loadingevent.cpp
 *
 *  Created on: 18.7.2012
 *      Author: akin
 */

#include "loadingevent.hpp"

namespace orion {

LoadingEvent::LoadingEvent( ResourceID ident , LoadingEvent::Type type )
: type( type ),
  id( ident )
{
}

LoadingEvent::LoadingEvent( const LoadingEvent& other )
: type( other.type ),
  id( other.id )
{
}

LoadingEvent::Type LoadingEvent::getType() const
{
	return type;
}

ResourceID LoadingEvent::getID() const
{
	return id;
}

} // namespace orion 
