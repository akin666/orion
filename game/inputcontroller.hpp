/*
 * inputcontroller.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef INPUTCONTROLLER_HPP_
#define INPUTCONTROLLER_HPP_

#include <orionevent>

namespace orion
{

class InputController : public EventListener< KeyEvent >
{
public:
	InputController();
	virtual ~InputController();

	virtual bool handle( const KeyEvent *const event , const int& count );
};

} /* namespace orion */
#endif /* INPUTCONTROLLER_HPP_ */
