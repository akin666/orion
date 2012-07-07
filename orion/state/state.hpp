/*
 * state.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include <orion>

namespace orion {

class State
{
public:
	State();
	virtual ~State();

	virtual void activate() = 0;
	virtual void run() = 0;
};

} // namespace orion
#endif // STATE_HPP_
