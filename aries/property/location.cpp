/*
 * location.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "location.hpp"
#include <entity/tproperty.hpp>

namespace orion {

Location::Location()
{
}

Location::~Location()
{
}

template <>
string8 TProperty<Location>::getName()
{
	return "location";
}

template <>
bool TProperty<Location>::parse( EntityID id , Json::Value& node )
{
	if( node == NULL )
	{
		return false;
	}
/*
	// Parse location data out of this bitch.
	rapidxml::xml_attribute<> *ax = node->first_attribute( "x" );
	if( ax != NULL )
	{
		// parse X
	}

	rapidxml::xml_attribute<> *ay = node->first_attribute( "y" );
	if( ay != NULL )
	{
		// parse Y
	}

	rapidxml::xml_attribute<> *az = node->first_attribute( "z" );
	if( az != NULL )
	{
		// parse Z
	}
/**/

	return true;
}

} // namespace orion
