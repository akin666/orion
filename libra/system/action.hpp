/*
 * action.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

namespace orion
{

class Action
{
public:
	Action();
	virtual ~Action();

	virtual void act() = 0;
};

} // namespace orion
#endif // ACTION_HPP_
