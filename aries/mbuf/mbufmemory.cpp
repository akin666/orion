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

bool Memory::open( Mode mode )
{
	if( array == NULL )
	{
		array = new ByteType[count];
		return true;
	}
	return false;
}

void Memory::close()
{
	delete[] array;
	array = NULL;
	count = 0;
}

bool Memory::ok() const
{
	return ( array != NULL ) && count > 0;
}

Buffer::Mode Memory::getMode() const
{
	return READWRITE;
}

} // namespace mmap
