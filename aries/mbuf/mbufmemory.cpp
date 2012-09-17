/*
 * mmapmemory.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbufmemory.hpp"
#include <iostream> // NULL

namespace mbuf {

Memory::Memory( std::size_t size )
: count( size ),
  array( NULL )
{
	array = new ByteType[size];
}

Memory::~Memory()
{
	close();
}

std::size_t Memory::size() const
{
	return count;
}

void *Memory::at( std::size_t position ) const
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
