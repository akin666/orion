/*
 * applicationinterface.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "applicationinterface.hpp"
#include <event/event.hpp>
#include <orion>

namespace orion {

ApplicationInterface::ApplicationInterface()
{
	attachListener<ApplicationEvent>( this );
}

ApplicationInterface::~ApplicationInterface()
{
	detachListener<ApplicationEvent>( this );
}

} // namespace orion
