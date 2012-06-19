/*
 * event.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 *
 *      Events should be thread safe.
 *      No matter where or when you sent em.
 */

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <orion>
#include <global>
#include <system/eventtask.hpp>
#include <system/scheduler.hpp>

namespace orion {

template <class CType>
void sendEvent( const CType& event )
{
	EventTask<CType> *handler = getGlobal< EventTask<CType> >();
	if( handler == NULL )
	{
		handler = createGlobal< EventTask<CType> >();
		createGlobal< Scheduler >()->add( handler );
	}
	handler->send( event );
}

template <class CType>
void attachListener( EventListener<CType> *listener )
{
	EventTask<CType> *handler = getGlobal< EventTask<CType> >();
	if( handler == NULL )
	{
		handler = createGlobal< EventTask<CType> >();
		createGlobal< Scheduler >()->add( handler );
	}
	handler->attach( listener );
}

template <class CType>
void detachListener( EventListener<CType> *listener )
{
	EventTask<CType> *handler = getGlobal< EventTask<CType> >();
	if( handler == NULL )
	{
		return; // No need to create..
	}
	handler->detach( listener );
}

} // orion

#endif // EVENT_HPP_
