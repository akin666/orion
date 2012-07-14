/*
 * property.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef PROPERTY_HPP_
#define PROPERTY_HPP_

#include <orion>
#include <rapidxml/rapidxml.hpp>
#include <json>

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

	virtual string8 getName();
	virtual bool parse( EntityID id , rapidxml::xml_node<> *node );
	virtual bool parse( EntityID id , Json::Value& node );
};

typedef std::vector< Property* > PropertySet;

} // namespace orion
#endif // PROPERTY_HPP_
