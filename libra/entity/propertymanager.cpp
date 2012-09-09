/*
 * propertymanager.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "propertymanager.hpp"

namespace orion {

// this basically holds a vector for every entity in the program, and that vector holds a pointer to properties that the entity has.
PropertyManager::PropertyMap PropertyManager::data;

void PropertyManager::attach( EntityID id , Property* property )
{
	PropertySet& pset = data[ id ];
	pset.push_back( property );
}

void PropertyManager::detach( EntityID id , Property* property )
{
	PropertySet& pset = data[ id ];

	for( PropertySet::iterator iter = pset.begin() ; iter != pset.end() ; ++iter )
	{
		if( *iter == property )
		{
			pset.erase( iter );
			return;
		}
	}
}

void PropertyManager::enable( bool enabled , EntityID id )
{
}

void PropertyManager::detachAll( EntityID id )
{
	PropertySet& pset = data[ id ];

	for( PropertySet::iterator iter = pset.begin() ; iter != pset.end() ; ++iter )
	{
		(*iter)->detach( id );
	}
}

} // namespace orion
