/*
 * eventtask.h
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef EVENTTASK_H_
#define EVENTTASK_H_

#include <orion>
#include <thread>
#include <event/eventlistener.hpp>

namespace orion {

class EventTaskInterface
{
public:
	EventTaskInterface();
	virtual ~EventTaskInterface();

	virtual void run() = 0;
};

template <class CType>
class EventTask : public EventTaskInterface
{
protected:
	typedef std::vector<CType> EventSet;
	typedef EventListener<CType> Listener;
	typedef std::vector< Listener* > ListenerSet;

	EventSet set1;
	EventSet set2;

	ListenerSet listeners;
	ListenerSet listenersTmp;

	std::mutex mset1;
	std::mutex mset2;
	std::mutex mlistener;

	std::mutex *mset;
	EventSet *set;
public:
	EventTask()
	{
		mset = &mset1;
		set = &set1;
	}
	virtual ~EventTask()
	{
	}

	void attach( Listener *listener )
	{
		std::lock_guard<std::mutex> lock( mlistener );
		listeners.push_back( listener );
	}

	void detach( Listener *listener )
	{
		std::lock_guard<std::mutex> lock( mlistener );

		for( typename ListenerSet::iterator iter = listeners.begin() ; iter != listeners.end() ; ++iter )
		{
			if( *iter == listener )
			{
				listeners.erase( iter );
				return;
			}
		}
	}

	void send( const CType& event )
	{
		std::lock_guard<std::mutex> lock( *mset );
		set->push_back( event );
	}

	virtual void run()
	{
		// Lock the currently performing mutex
		EventSet *process = NULL;
		{
			std::lock_guard<std::mutex> lock( *mset );

			// switch sets
			if( mset == &mset1 )
			{
				mset = &mset2;
				set = &set2;
				process = &set1;
			}
			else
			{
				mset = &mset1;
				set = &set1;
				process = &set2;
			}
		}

		{
			// Copy listener list..
			std::lock_guard<std::mutex> lock( mlistener );
			listenersTmp = listeners;
		}
		// no need to lock..
		// go through the process set.
		for( typename EventSet::iterator message = process->begin() ; message != process->end() ; ++message )
		{
			// send the event to listeners..
			for( typename ListenerSet::iterator iter = listenersTmp.begin() ; iter != listenersTmp.end() ; ++iter )
			{
				if( (*iter)->handle( *message ) )
				{
					// listener handled the event.
					break;
				}
			}
		}
		// empty events.
		process->clear();
	}
};

} // namespace orion
#endif // EVENTTASK_H_
