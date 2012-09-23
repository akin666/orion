/*
 * mmapmemory.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbufmemory.hpp"
#include <iostream> // NULL

namespace mbuf {

Memory::Memory( std::size_t size , std::size_t alignment )
: count( size )
, alignment( alignment )
, array( NULL )
, begin( NULL )
{
}

Memory::~Memory()
{
	delete[] begin;
	begin = NULL;
	array = NULL;
}

Memory& Memory::setSize( std::size_t filesize )
{
	count = filesize;
	return *this;
}

Memory& Memory::setAlignment( std::size_t alignment )
{
	this->alignment = alignment;
	return *this;
}

void Memory::initialize()
{
	if( array == NULL )
	{
		begin = new ByteType[count + alignment];
		long at = (long)(begin);
		at += (alignment - (at%((long)alignment)));
		array = (ByteType*)at;
	}
}

std::size_t Memory::size() const
{
	return count;
}

void *Memory::retain( std::size_t position , std::size_t count )
{
	return (void*)((long)array + position);
}

void Memory::release( void *buffer )
{
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
