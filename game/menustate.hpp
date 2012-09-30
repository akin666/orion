/*
 * menustate.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include <state/state.hpp>

namespace orion
{

class Scheduler;
class MenuState : public State
{
protected:
	Scheduler *scheduler;
public:
	MenuState();
	virtual ~MenuState();

	virtual void activate();
	virtual void run();
	virtual bool canExit();
	virtual void exit();
};

} // namespace orion
#endif // MENUSTATE_HPP_
