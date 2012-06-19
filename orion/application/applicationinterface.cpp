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

	setGlobal<ApplicationInterface>( this );
}

ApplicationInterface::~ApplicationInterface()
{
	detachListener<ApplicationEvent>( this );

	setGlobal<ApplicationInterface>( NULL );
}

void ApplicationInterface::run()
{
	createGlobal< Scheduler >()->run();
}

} // namespace orion
