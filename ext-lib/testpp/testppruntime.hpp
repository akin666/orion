/*
 * testppruntime.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#ifndef TESTPPRUNTIME_HPP_
#define TESTPPRUNTIME_HPP_

#include <vector>
#include "testpptest.hpp"
#include "testppoutput.hpp"

namespace testpp
{

class Runtime
{
private:
	typedef std::vector<Test*> TestSet;
	TestSet tests;
	Output& output;
public:
	Runtime( Output& output );
	~Runtime();

	template <class TestClass> void add()
	{
		Test *test = new TestClass;
		tests.push_back( test );
	}

	void clear();

	void run();
};

} // namespace testpp
#endif // TESTPPRUNTIME_HPP_
