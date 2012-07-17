/*
 * loadingevent.hpp
 *
 *  Created on: 18.7.2012
 *      Author: akin
 */

#ifndef LOADINGEVENT_HPP_
#define LOADINGEVENT_HPP_

#include <orion>

namespace orion {

class LoadingEvent
{
public:
	enum Type {
		Started = 0x01,
		Loading = 0x02,
		Error	= 0x04,
		Finished = 0x10,
		NotFound = 0x20,
	};
protected:
	Type type;
	ResourceID id;
public:
	LoadingEvent( ResourceID ident , Type type );
	LoadingEvent( const LoadingEvent& other );
	virtual ~LoadingEvent();

	Type getType() const;
	ResourceID getID() const;
};

} // namespace orion 
#endif // LOADINGEVENT_HPP_ 
