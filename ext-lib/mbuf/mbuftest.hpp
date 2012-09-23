/*
 * mbuftest.hpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#ifndef HMBUFTEST_HPP_
#define HMBUFTEST_HPP_

#include <testpp/testpptest.hpp>

namespace mbuf {

class Test : public testpp::Test
{
public:
	Test();
	virtual ~Test();

	virtual std::string getName() const;

	//
	// returning false, equals, No other test will be performed.
	// if it means 'test fail' then indicate that in Success.
	virtual bool init();
	virtual bool run();
	virtual bool clean();

	virtual Success success();
	virtual std::string logMessage();
};

} // namespace mbuf
#endif // MBUFTEST_HPP_
