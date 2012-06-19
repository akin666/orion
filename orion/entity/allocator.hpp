/*
 * allocator.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 *
 *      TODO!
 */

#ifndef ALLOCATOR_HPP_
#define ALLOCATOR_HPP_

#include <orion>

namespace orion {

class Allocator
{
public:
	static void set( Allocator *allocator );
	static Allocator *get();
protected:
	static Allocator *allocator;
protected:
	// own data..
public:
	Allocator();
	virtual ~Allocator();

	template <class CType>
	CType *create()
	{
		return new CType;
	}

	template <class CType>
	void destroy( CType* data )
	{
		delete data;
	}
};

} // namespace orion
#endif // ALLOCATOR_HPP_
