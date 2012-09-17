/*
 * mmapmemory.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mmapmemory.hpp"
#include <iostream> // NULL

namespace mmap {

Memory::Memory( Size size )
: count( size ),
  array( NULL )
{
	array = new ByteType[size];
}

Memory::~Memory()
{
	close();
}

Memory::Size Memory::size() const
{
	return count;
}

void *Memory::at( Memory::Size position ) const
{
	return (void*)((long)array + position);
}

void Memory::close()
{
	delete[] array;
	array = NULL;
	count = 0;
}

bool Memory::ok()
{
	return ( array != NULL ) && count > 0;
}

} // namespace mmap
