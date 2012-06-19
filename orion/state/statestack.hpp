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

class StateStack {
protected:
	typedef std::vector<State*> StateSet;

	StateSet states;

	State *last;
	State *current;
public:
	StateStack();
	virtual ~StateStack();

	void runStateStack();

	void push( State& state );
	void pop( State& state );
};

} // namespace orion
#endif // STATESTACK_HPP_
