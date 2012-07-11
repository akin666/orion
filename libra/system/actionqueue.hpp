/*
 * actionqueue.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#ifndef ACTIONQUEUE_HPP_
#define ACTIONQUEUE_HPP_

#include <orion>
#include "action.hpp"

namespace orion
{

class ActionQueue
{
public:
	class Item
	{
	public:
		Tick tick;
		Action *action;

		Item()
		: tick( 0 ),
		  action( NULL )
		{
		}

		Item( const Item& other )
		: tick( other.tick ),
		  action( other.action )
		{
		}

		Item( Tick tick , Action *action )
		:  tick( tick ),
		   action( action )
		{
		}
	};

protected:
	typedef std::list<Item> ActionSet;
	ActionSet items;
public:
	ActionQueue();
	virtual ~ActionQueue();

	void add( Tick time , Action *action );
	void run( Tick time );
};

} // namespace orion
#endif // ACTIONQUEUE_HPP_
