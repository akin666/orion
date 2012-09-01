/*
 * eventlistener.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

namespace orion {

template <class EventType>
class EventListener {
public:
	EventListener() {}
	virtual ~EventListener() {}

	// Handle a batch of events
	virtual bool handle( const EventType *const event , const int& count ) { return false; }
};

} // namespace orion
#endif // EVENTLISTENER_HPP_
