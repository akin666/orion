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
  value( 0 ),
  code( 0 )
{
}

KeyEvent::KeyEvent( const KeyEvent& other )
: action( other.action ),
  value( other.value ),
  code( other.code )
{
}

KeyEvent::KeyEvent( Action action , UNICODE value , uint32 code , uint32 device )
: action( action ),
  value( value ),
  code( code ),
  device( device )
{
}

KeyEvent::~KeyEvent()
{
}

} // namespace orion
