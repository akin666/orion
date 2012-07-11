/*
 * motionevent.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef MOTIONEVENT_HPP_
#define MOTIONEVENT_HPP_

#include <orion>

namespace orion
{

class MotionEvent
{
public:
	MotionEvent();
	MotionEvent( const MotionEvent& other );
	MotionEvent( glm::vec2 delta , glm::vec2 position , uint32 device = 0 );
	virtual ~MotionEvent();

	glm::vec2 delta;
	glm::vec2 position;
	uint32 device;
};

} // namespace orion
#endif // MOTIONEVENT_HPP_
