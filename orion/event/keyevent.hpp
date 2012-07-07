/*
 * keyevent.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef KEYEVENT_HPP_
#define KEYEVENT_HPP_

#include <orion>

namespace orion
{

class KeyEvent
{
public:
	enum Action {
		None = 0x0000,
		Down = 0x0001,
		Up = 0x0002,
		Triggered = Up
	};
public:
	KeyEvent();
	KeyEvent( const KeyEvent& other );
	KeyEvent( Action action , UNICODE value , uint32 code , uint32 device = 0 );
	virtual ~KeyEvent();

	Action action;
	UNICODE value;
	uint32 code;
	uint32 device;
};

} // namespace orion
#endif // KEYEVENT_HPP_
