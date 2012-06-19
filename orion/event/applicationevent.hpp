/*
 * applicationevent.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef APPLICATIONEVENT_HPP_
#define APPLICATIONEVENT_HPP_

namespace orion {

class ApplicationEvent
{
public:
	enum Type {
		None = 0,
		Started,
		Stopped,
		Resumed,
		Paused,
		Minimized,
		Maximized,
		Windowed,
		Resized,
	};

	Type type;
public:
	ApplicationEvent();
	ApplicationEvent( const ApplicationEvent& other );
	virtual ~ApplicationEvent();
};

} // namespace orion
#endif // APPLICATIONEVENT_HPP_
