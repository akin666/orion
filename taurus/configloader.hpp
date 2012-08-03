/*
 * configloader.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef CONFIGLOADER_HPP_
#define CONFIGLOADER_HPP_

#include <config/config.hpp>

namespace orion
{

class ConfigLoader
{
public:
	ConfigLoader();
	virtual ~ConfigLoader();

	virtual bool load( Config& container );
};

} // namespace orion
#endif // CONFIGLOADER_HPP_
