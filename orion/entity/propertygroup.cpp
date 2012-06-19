/*
 * propertygroup.cpp
 *
 *  Created on: 19.6.2012
 *      Author: akin
 */

#include "propertygroup.hpp"
#include "entity.hpp"

namespace orion {

PropertyGroup::PropertyGroup()
{
}

PropertyGroup::~PropertyGroup()
{
}

void PropertyGroup::attach( Property *property )
{
	if( property == NULL )
	{
		return;
	}
	properties[ property->getName() ] = property;
}

void PropertyGroup::detach( Property *property )
{
	if( property == NULL )
	{
		return;
	}
	PropertyMap::iterator iter = properties.find( property->getName() );

	if( iter != properties.end() )
	{
		properties.erase( iter );
	}
}

bool PropertyGroup::parse( EntityID id , rapidxml::xml_node<> *node )
{
	if( id == Entity::null || node == NULL )
	{
		return false;
	}

	bool success = true;
	do
	{
		PropertyMap::iterator iter = properties.find( std::string( node->name() ) );

		if( iter != properties.end() )
		{
			success = iter->second->parse( id , node ) && success;
		}
	}
	while( (node = node->next_sibling()) != NULL );

	return success;
}

} // namespace orion
