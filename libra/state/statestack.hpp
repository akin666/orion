/*
 * statestack.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef STATESTACK_HPP_
#define STATESTACK_HPP_

#include "state.hpp"

namespace orion {

class StateStack
{
protected:
	typedef std::vector<State*> StateSet;

	StateSet states;

	State *last;
	State *current;

	void destroy( State *state );
public:
	StateStack();
	virtual ~StateStack();

	void run();

	void pop();

	// The allocation is managed by the stack, if you want to modify the thing, then use the returned reference.
	template <class CType>
	CType& push();

	// The allocation is managed by the stack, if you want to modify the thing, then use the returned reference.
	template <class CType>
	CType& replace();
};

template <class CType>
CType& StateStack::push<CType>()
{
	if( current != NULL )
	{
		states.push_back( current );
	}

	return *(current = new CType);
}

template <class CType>
CType& StateStack::replace<CType>()
{
	pop();
	return push<CType>();
}

} // namespace orion
#endif // STATESTACK_HPP_
