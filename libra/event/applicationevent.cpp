/*
 * applicationevent.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "applicationevent.hpp"

namespace orion {

ApplicationEvent::ApplicationEvent()
{
}

ApplicationEvent::ApplicationEvent( const ApplicationEvent& other )
: type( other.type )
{
}

ApplicationEvent::ApplicationEvent( Type type  )
: type( type )
{
}

} // namespace orion
