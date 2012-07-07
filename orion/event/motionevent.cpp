/*
 * motionevent.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "motionevent.hpp"

namespace orion
{

MotionEvent::MotionEvent()
: device( 0 )
{
}

MotionEvent::MotionEvent( const MotionEvent& other )
: delta( other.delta ),
  position( other.position ),
  device( other.device )
{
}

MotionEvent::MotionEvent( glm::vec2 delta , glm::vec2 position , uint32 device )
: delta( delta ),
  position( position ),
  device( device )
{
}

MotionEvent::~MotionEvent()
{
}

} // namespace orion
