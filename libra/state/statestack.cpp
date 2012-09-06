/*
 * statestack.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "statestack.hpp"

namespace orion {

StateStack::StateStack()
: last( NULL ),
  current( NULL )
{
}

StateStack::~StateStack()
{
	// Destroy the states
	while( current != NULL )
	{
		pop();
	}
}

void StateStack::destroy( State *state )
{
	if( state != NULL )
	{
		delete state;
	}
}

void StateStack::run()
{
	State *current = this->current;
	if( current != last )
	{
		if( current != NULL )
		{
			current->activate();
		}
	}

	if( current != NULL )
	{
		current->run();
	}

	last = current;
}

void StateStack::pop()
{
	if( current != NULL )
	{
		destroy( current );
		current = NULL;
	}
	if( states.size() > 0 )
	{
		current = states.back();
		states.pop_back();
	}
}

} // namespace orion
