/*
 * resourcemanager.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

namespace orion
{

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	virtual bool initialize();
};

} // namespace orion
#endif // RESOURCEMANAGER_HPP_
