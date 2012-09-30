/*
 * statestack.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "statestack.hpp"
#include <deque>

namespace orion {

StateStack::StateStack()
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
	// Creation activation.
	if( activateList.size() > 0 )
	{
		StateSet tmplist;
		// critical section, copies the activatelist.
		{
			std::lock_guard<std::mutex> lock( addmutex );
			tmplist = activateList;
			activateList.clear();
		}

		for( StateSet::iterator iter = tmplist.begin() ; iter != tmplist.end() ; ++iter )
		{
			State *current = *this;
			current->activate();

			states.push_back( current );
		}
	}

	typedef std::deque<StateSet::iterator> RemoveSet;
	RemoveSet rmSet;
	for( StateSet::iterator iter = states.begin() ; iter != states.end() ; ++iter )
	{
		State *current = *iter;
		current->run();

		if( current->canExit() )
		{
			current->exit();
			destroy( state );
			rmSet.push_front( iter );
		}
	}
	for( RemoveSet::iterator iter = rmSet.begin() ; iter != rmSet.end() ; ++iter )
	{
		states.erase( *iter );
	}
}

} // namespace orion
