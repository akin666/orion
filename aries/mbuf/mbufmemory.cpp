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

Memory& Memory::setSize( std::size_t filesize )
{
	count = filesize;
	return *this;
}

void Memory::initialize()
{
	if( array == NULL )
	{
		array = new ByteType[count];
	}
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
	initialize();
	return array != NULL;
}

void Memory::close()
{
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
