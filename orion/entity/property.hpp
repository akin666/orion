/*
 * property.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef PROPERTY_HPP_
#define PROPERTY_HPP_

#include <orion>

namespace orion {

class Property
{
protected:
	virtual void attachEntity( EntityID id );
	virtual void detachEntity( EntityID id );
public:
	Property();
	virtual ~Property();

	void attach( EntityID id );
	void detach( EntityID id );

	virtual bool has( EntityID id );
};

typedef std::vector< Property* > PropertySet;

} // namespace orion
#endif // PROPERTY_HPP_
