/*
 * property.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "property.hpp"
#include "propertymanager.hpp"

namespace orion {

Property::Property()
{
}

Property::~Property()
{
}

void Property::attachEntity( EntityID id )
{
}

void Property::detachEntity( EntityID id )
{
}

void Property::enableEntity( bool enabled , EntityID id )
{
}

void Property::attach( EntityID id )
{
	PropertyManager::attach( id , this );
	attachEntity( id );
}

void Property::detach( EntityID id )
{
	PropertyManager::detach( id , this );
	detachEntity( id );
}

void Property::enable( bool enabled , EntityID id )
{
	enableEntity( enabled , id );
}

bool Property::has( EntityID id )
{
	return false;
}

string8 Property::getName()
{
	return "null";
}

bool Property::parse( EntityID id , Json::Value& node )
{
	return false;
}

} // namespace orion
