/*
 * propertyfactory.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef PROPERTYFACTORY_HPP_
#define PROPERTYFACTORY_HPP_

#include <orion>

namespace orion {

class PropertyFactory {
public:
	PropertyFactory();
	virtual ~PropertyFactory();

	virtual void attach( EntityID id , rapidxml::xml_node<> *node );
};

} // namespace orion
#endif // PROPERTYFACTORY_HPP_
