/*
 * propertygroup.hpp
 *
 *  Created on: 19.6.2012
 *      Author: akin
 */

#ifndef PROPERTYGROUP_HPP_
#define PROPERTYGROUP_HPP_

#include <orion>
#include "property.hpp"

namespace orion {

class PropertyGroup {
protected:
	typedef std::map< std::string , Property* > PropertyMap;
	PropertyMap properties;
public:
	PropertyGroup();
	virtual ~PropertyGroup();

	void attach( Property *property );
	void detach( Property *property );

	bool parse( EntityID id , rapidxml::xml_node<> *node );
};

} // namespace orion */
#endif // PROPERTYGROUP_HPP_ */
