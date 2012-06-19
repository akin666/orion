/*
 * location.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <orion>

namespace orion {

class Location
{
protected:
	glm::mat4 position;
public:
	Location();
	virtual ~Location();
};

} // namespace orion
#endif // LOCATION_HPP_
