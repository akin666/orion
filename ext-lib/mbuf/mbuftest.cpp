/*
 * mbuftest.cpp
 *
 *  Created on: Sep 23, 2012
 *      Author: mkorpela
 */

#include "mbuftest.hpp"

namespace mbuf {

Test::Test()
{
}

Test::~Test()
{
}

std::string Test::getName() const
{
	return __FILE__;
}

bool Test::init()
{
	return true;
}

bool Test::run()
{
	return true;
}

bool Test::clean()
{
	return true;
}

Test::Success Test::success()
{
	return ERROR;
}

std::string Test::logMessage()
{
	return "Not enough gears";
}

} // namespace mbuf
