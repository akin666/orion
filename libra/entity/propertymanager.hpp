/*
 * propertymanager.h
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef PROPERTYMANAGER_H_
#define PROPERTYMANAGER_H_

#include "property.hpp"

namespace orion {

class PropertyManager {
protected:
	typedef std::map< EntityID , PropertySet > PropertyMap;

	static PropertyMap data;
public:
	static void attach( EntityID id , Property* property );
	static void detach( EntityID id , Property* property );

	static void enable( bool enabled , EntityID id );

	static void detachAll( EntityID id );
};

} // namespace orion
#endif // PROPERTYMANAGER_H_
