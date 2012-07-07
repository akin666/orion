/*
 * menustate.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "menustate.hpp"
#include <system/scheduler.hpp>

namespace orion
{

MenuState::MenuState()
: scheduler( NULL )
{
}

MenuState::~MenuState()
{
}

void MenuState::activate()
{
	scheduler = Global<Scheduler>::get();

	if( scheduler != NULL )
	{
		// Reset the Tick time.
		scheduler->setCurrent( 0 );
		scheduler->setRenderTick( 0 );
	}
}

void MenuState::run()
{
	if( scheduler != NULL )
	{
		// Reset the Tick time.
		scheduler->setRenderTick( scheduler->getCurrent() + 1 );
	}
}

} // namespace orion
