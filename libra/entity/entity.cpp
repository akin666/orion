/*
 * entity.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "entity.hpp"
#include "propertymanager.hpp"

#define FIRST_ENTITY 32

namespace orion {

const EntityID Entity::null = 0;
EntityID Entity::current = FIRST_ENTITY;

EntityID Entity::create()
{
	return ++current;
}

void Entity::destroy( EntityID id )
{
	if( id == null )
	{
		return;
	}
	// Destroy ID
	// (or at least, all its datasets)
	PropertyManager::detachAll( id );
}

Entity::Entity()
: id( create() )
{
}

Entity::~Entity()
{
	destroy( id );
	id = null;
}

} // namespace orion
