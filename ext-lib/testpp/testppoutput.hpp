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
	virtual ~Output();

	// Evaluate, if we can still continue, even after the module
	// failed, errorously, or critically, or it passed..
	virtual bool eval( int number , const std::string& module , Test::Success success , const std::string& str );
};

} // namespace testpp
#endif // TESTPPOUTPUT_HPP_
