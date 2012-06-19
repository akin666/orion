/*
 * location.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "location.hpp"
#include <entity/TProperty.hpp>

namespace orion {

Location::Location()
{
}

Location::~Location()
{
}

template <>
std::string TProperty<Location>::getName()
{
	return "location";
}

template <>
bool TProperty<Location>::parse( EntityID id , rapidxml::xml_node<> *node )
{
	if( node == NULL )
	{
		return false;
	}

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

	return true;
}

} // namespace orion
