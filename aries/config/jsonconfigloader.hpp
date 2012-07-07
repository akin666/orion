/*
 * JSONCONFIGLOADER_HPP_.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef JSONCONFIGLOADER_HPP_
#define JSONCONFIGLOADER_HPP_

#include <loader>
#include <config/config.hpp>

namespace orion
{

class JSONConfigLoader : public Loader<Config>
{
public:
	JSONConfigLoader();
	virtual ~JSONConfigLoader();

	virtual bool load( Config& container );
};

} // namespace orion
#endif // JSONCONFIGLOADER_HPP_
