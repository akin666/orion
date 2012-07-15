/*
 * entity.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <orion>

namespace orion {

class Entity
{
protected:
	static std::atomic<EntityID> current;
public:
	static const EntityID null;

	static EntityID create();
	static void destroy( EntityID id );
public:
	EntityID id;

	Entity();
	virtual ~Entity();
};

} /* namespace orion */
#endif /* ENTITY_HPP_ */
