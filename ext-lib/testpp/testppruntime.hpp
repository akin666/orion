/*
 * testppruntime.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 *
 *
 *  use:
 *  {
 *  	Runtime<Output> runtime;		// Runtime using output class Output
 *  	runtime.add<mbuf::Test>();		// run module mbuf tests
 *  	runtime.add<graphics::Test>();	// run module graphics tests
 *  	runtime.add<audio::Test>();		// run module audio tests
 *  	runtime.add<input::Test>();		// run module input tests
 *  	runtime.run();					// run the batch
 *  }
 */

#ifndef TESTPPRUNTIME_HPP_
#define TESTPPRUNTIME_HPP_

#include <vector>
#include "testpptest.hpp"
#include "testppoutput.hpp"

namespace testpp
{

template <class OutputProperty>
class Runtime
{
private:
	typedef std::vector<Test*> TestSet;
	TestSet tests;
	OutputProperty output;
public:
	Runtime()
	{
	}

	~Runtime()
	{
		clear();
	}

	template <class TestClass> void add()
	{
		Test *test = new TestClass;
		tests.push_back( test );
	}

	void clear()
	{
		for( TestSet::iterator iter = tests.begin() ; iter != tests.end() ; ++iter )
		{
			delete *iter;
		}
		tests.clear();
	}

	void run()
	{
		for( TestSet::iterator iter = tests.begin() ; iter != tests.end() ; ++iter )
		{
			// Measure success..
			// And possibly Log it.
			if( !output.eval( *iter ) )
			{
				break;
			}
		}
	}
};

} // namespace testpp
#endif // TESTPPRUNTIME_HPP_
