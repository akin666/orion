/*
 * testppoutput.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#ifndef TESTPPOUTPUT_HPP_
#define TESTPPOUTPUT_HPP_

#include "testpptest.hpp"

namespace testpp {

class Output
{
public:
	Output();
	~Output();

	// Evaluate, if we can still continue, even after the module
	// failed, errorously, or critically, or it passed..
	bool eval( Test *test );
};

} // namespace testpp
#endif // TESTPPOUTPUT_HPP_
