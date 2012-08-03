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
	enum Type {
		Mouse = 0x0001,
		Keyboard = 0x0002,
		Touch = 0x0004,
		Joystick = 0x0008,
		Extra = 0x0010
	};
public:
	KeyEvent();
	KeyEvent( const KeyEvent& other );
	KeyEvent( Action action , Type type, UNICODE value , uint32 code , uint32 device = 0 );
	KeyEvent( Action action , Type type, UNICODE value , uint32 code , glm::vec2 position , uint32 device = 0 );

	Action action;
	Type type;
	UNICODE value;
	uint32 code;
	uint32 device;
	glm::vec2 position;
};

} // namespace orion
#endif // KEYEVENT_HPP_
