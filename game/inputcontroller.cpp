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

bool InputController::handle( const KeyEvent *const event , const int& count )
{
	LOG->message( "Got %i , %i , %i , %i " , event[0].action , event[0].value , event[0].code , event[0].device );

	return true;
}

} /* namespace orion */
