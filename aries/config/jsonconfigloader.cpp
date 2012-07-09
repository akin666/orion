/*
 * JSONConfigLoader.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "jsonconfigloader.hpp"

#include <JsonBox.h>
#include <native>

#ifndef DEFAULT_CONFIG_PATH
# define DEFAULT_CONFIG_PATH "config.json"
#endif

namespace orion
{

JSONConfigLoader::JSONConfigLoader()
{
}

JSONConfigLoader::~JSONConfigLoader()
{
}

bool JSONConfigLoader::load( Config& container )
{
	std::string content;
	if( !readFile( DEFAULT_CONFIG_PATH , content ) )
	{
		return false;
	}
	return container.loadFromString( content );
}

} // namespace orion
