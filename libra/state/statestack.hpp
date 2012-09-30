/*
 * statestack.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef STATESTACK_HPP_
#define STATESTACK_HPP_

#include "state.hpp"
#include <uthread>

namespace orion {

class StateStack
{
protected:
	typedef std::vector<State*> StateSet;
	StateSet states;
	StateSet activateList;

	std::mutex addmutex;

	void destroy( State *state );
public:
	StateStack();
	virtual ~StateStack();

	void run();

	// The allocation is managed by the stack, if you want to modify the thing, then use the returned reference.
	template <class CType>
	CType& push()
	{
		std::lock_guard<std::mutex> lock( addmutex );
		CType *tmp = new CType;

		activateList.push_back( tmp );

		return *tmp;
	}
};

} // namespace orion
#endif // STATESTACK_HPP_
