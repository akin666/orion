/*
 * actionqueue.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "actionqueue.hpp"
#include <algorithm>

namespace orion
{

bool actionSort( const ActionQueue::Item& a , const ActionQueue::Item& b )
{
	return a.tick < b.tick;
}

ActionQueue::ActionQueue()
{
}

ActionQueue::~ActionQueue()
{
}

void ActionQueue::add( Tick time , Action *action )
{
	if( action == NULL )
	{
		return;
	}
	items.push_back( Item( time , action ) );
	items.sort( actionSort );
}

void ActionQueue::run( Tick time )
{
	for( ActionSet::iterator iter = items.begin() ; iter != items.end() ; ++iter )
	{
		if( iter->tick > time )
		{
			if( iter != items.begin() )
			{
				items.erase( items.begin() , iter );
			}
			return;
		}
		iter->action->act();
	}
}

} // namespace orion
