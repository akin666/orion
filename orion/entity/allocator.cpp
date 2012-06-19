/*
 * allocator.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "allocator.hpp"

namespace orion {

Allocator *Allocator::allocator = NULL;

void Allocator::set( Allocator *allocator )
{
	Allocator::allocator = allocator;
}

Allocator *Allocator::get()
{
	if( allocator == NULL )
	{
		allocator = new Allocator;
	}
	return allocator;
}

Allocator::Allocator()
{
}

Allocator::~Allocator()
{
}

} // namespace orion
