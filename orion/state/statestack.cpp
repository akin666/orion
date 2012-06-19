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
}

void StateStack::runStateStack()
{
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

void StateStack::push( State& state )
{
	if( current != NULL )
	{
		states.push_back( current );
	}
	current = &state;
}

void StateStack::pop( State& state )
{
	if( current == &state )
	{
		if( states.size() > 0 )
		{
			current = states.back();
			states.pop_back();
		}
		else
		{
			current = NULL;
		}
	}
}

} // namespace orion
