/*
 * mbufbuffer.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbufbuffer.hpp"
#include <cassert>

namespace mbuf {

Buffer::Iterator::Iterator( const Iterator& other )
: buffer( other.buffer ),
  iter( other.iter )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
}

Buffer::Iterator::Iterator( const Buffer& buffer , std::size_t at )
: buffer( buffer ),
  iter( at )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
}

std::size_t Buffer::Iterator::position() const
{
	return iter;
}

void Buffer::Iterator::jump( std::size_t size )
{
	iter += size;
	if( iter > buffer.size() )
	{
		iter = buffer.size();
	}
}

void Buffer::Iterator::seek( std::size_t at )
{
	iter = at;
}

Buffer::Iterator Buffer::begin() const
{
	return Iterator( *this , 0 );
}

Buffer::Iterator Buffer::end() const
{
	return Iterator( *this , size() );
}

} // namespace mbuf

