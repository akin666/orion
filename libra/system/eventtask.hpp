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

#include <profiler/profilerdata.hpp>

#ifndef INITIALIZE_EVENTSET_SIZE
# define INITIALIZE_EVENTSET_SIZE 64
#endif

namespace orion {

class EventTaskInterface
{
public:
	EventTaskInterface();
	virtual ~EventTaskInterface();

	// return true, if an event was processed.
	virtual bool run() = 0;

	ProfilerData profiler;
};

template <class CType>
class EventTask : public EventTaskInterface
{
protected:
	typedef std::vector<CType> EventSet;
	typedef EventListener<CType> Listener;
	typedef std::vector< Listener* > ListenerSet;

	std::atomic<uint32> low;
	std::atomic<uint32> high;
	std::atomic<uint32> count;
	std::atomic<uint32> size;

	EventSet set;
	EventSet tmpSet;
	EventSet tmpSet2;

	ListenerSet listeners;
	std::mutex mlistener;
	std::mutex consuming;
public:
	EventTask()
	{
		low = 0;
		high = 0;
		size = INITIALIZE_EVENTSET_SIZE;
		set.resize( size );
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
		uint32 spot = high++;
		count++;
		set[ spot%size ] = event;

		if( count > size )
		{
			LOG->error( "Event overflow! %s:%i" , __FILE__ , __LINE__ );
		}
	}

	void sendDirect( const CType& event )
	{
		ListenerSet listenersTmp;
		{
			// Copy listener list..
			std::lock_guard<std::mutex> lock( mlistener );
			listenersTmp = listeners;
		}
		for( typename ListenerSet::iterator iter = listenersTmp.begin() ; iter != listenersTmp.end() ; ++iter )
		{
			if( (*iter)->handle( &event , 1 ) )
			{
				// listener handled the event.
				break;
			}
		}
	}

	virtual bool run()
	{
		// Lock the currently performing mutex
		uint32 from;
		uint32 to;
		int32 count;

		tmpSet.clear();
		{
			std::lock_guard<std::mutex> lock( consuming );
			from = low;
			to = high;
			low = to;

			count = to - from;
			this->count -= count;

			if( count < 1 )
			{
				return false;
			}

			// Copy the events.
			// Hopefully copies the whole block, reusing the mem..
			tmpSet = set;
		}

		uint32 begin = from % size;
		uint32 end   = to % size;

		ListenerSet listenersTmp;
		{
			// Copy listener list..
			std::lock_guard<std::mutex> lock( mlistener );
			listenersTmp = listeners;
		}

		// because of the ringbuffer, the array is not linear always.
		// it might be also [ a -> end ] [ begin -> b ]
		// Need to reorder it..
		if( begin > end )
		{
			tmpSet2 = tmpSet;
			for( int i = 0 ; i < count ; ++i )
			{
				tmpSet[i] = tmpSet2[(begin+i)%size];
			}
			begin = 0;
			end = count;
		}

		// go through the process set.
		const CType *const events = &tmpSet[begin];
		// send the eventbatch to listeners..
		for( typename ListenerSet::iterator iter = listenersTmp.begin() ; iter != listenersTmp.end() ; ++iter )
		{
			if( (*iter)->handle( events , count ) )
			{
				// listener handled the batch.
				break;
			}
		}

		return true;
	}
};

} // namespace orion
#endif // EVENTTASK_H_
