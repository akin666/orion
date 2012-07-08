/*
 * JSONConfigLoader.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "jsonconfigloader.hpp"

#include <JsonBox.h>

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
	return container.loadFromFile( DEFAULT_CONFIG_PATH );
}

} // namespace orion
