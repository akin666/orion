/*
 * testpptest.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#ifndef TESTPPTEST_HPP_
#define TESTPPTEST_HPP_

namespace testpp
{

class Test
{
public:
	enum Success
	{
		OK = 		0x0001,
		ERROR  = 	0x0002,
		CRITICAL = 	0x0004,
	};
public:
	Test();
	virtual ~Test();

	virtual std::string getName() const = 0;

	virtual bool init() = 0;
	virtual bool run() = 0;
	virtual bool clean() = 0;

	virtual Success success() = 0;
	virtual std::string logMessage() = 0;
};

} // namespace testpp
#endif // TESTPPTEST_HPP_
