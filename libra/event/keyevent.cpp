/*
 * keyevent.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "keyevent.hpp"

namespace orion
{

KeyEvent::KeyEvent()
: action( None ),
  type( Extra ),
  value( 0 ),
  code( 0 ),
  device( 0 )
{
}

KeyEvent::KeyEvent( const KeyEvent& other )
: action( other.action ),
  type( other.type ),
  value( other.value ),
  code( other.code ),
  device( other.device ),
  position( other.position )
{
}

KeyEvent::KeyEvent( Action action , Type type , UNICODE value , uint32 code , uint32 device )
: action( action ),
  type( type ),
  value( value ),
  code( code ),
  device( device )
{
}

KeyEvent::KeyEvent( Action action , Type type , UNICODE value , uint32 code , glm::vec2 position , uint32 device )
: action( action ),
  type( type ),
  value( value ),
  code( code ),
  device( device ),
  position( position )
{
}

} // namespace orion
