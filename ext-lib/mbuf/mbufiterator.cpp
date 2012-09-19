/*
 * mbufiterator.cpp
 *
 *  Created on: 19.9.2012
 *      Author: akin
 */

#include "mbufiterator.hpp"
#include "mbufbuffer.hpp"
#include <cassert>

namespace mbuf
{

void *Iterator::at( std::size_t it ) const
{
	return buffer.at( it );
}

Iterator::Iterator( const Iterator& other )
: buffer( other.buffer ),
  iter( other.iter )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
	++buffer.ref_count;
}

Iterator::Iterator( Buffer& buffer , std::size_t at )
: buffer( buffer ),
  iter( at )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
	++buffer.ref_count;
}

Iterator::~Iterator()
{
	--buffer.ref_count;
}

std::size_t Iterator::position() const
{
	return iter;
}

std::size_t Iterator::remaining() const
{
	return buffer.size() - iter;
}

void Iterator::jump( std::size_t size )
{
	iter += size;
	if( iter > buffer.size() )
	{
		iter = buffer.size();
	}
}

void Iterator::seek( std::size_t at )
{
	iter = at;
}

void *Iterator::peek() const
{
	return at( iter );
}

bool Iterator::finished() const
{
	return iter >= buffer.size();
}

void Iterator::reset()
{
	iter = 0;
}

} // namespace mbuf
