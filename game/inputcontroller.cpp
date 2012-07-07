/*
 * inputcontroller.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "inputcontroller.hpp"
#include <orion>

namespace orion
{

InputController::InputController()
{
	attachListener<KeyEvent>( this );
}

InputController::~InputController()
{
	detachListener<KeyEvent>( this );
}

bool InputController::handle( const KeyEvent& event )
{
	LOG->message( "Got %i , %i , %i , %i " , event.action , event.value , event.code , event.device );

	return true;
}

} /* namespace orion */
