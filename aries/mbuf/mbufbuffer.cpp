/*
 * mbufbuffer.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbufbuffer.hpp"

namespace mbuf {

Buffer::Iterator::Iterator( const Iterator& other )
: buffer( other.buffer ),
  iter( other.iter )
{
}

Buffer::Iterator::Iterator( const Buffer& buffer , Size at )
: buffer( buffer ),
  iter( at )
{
}

Buffer::Size Buffer::Iterator::position() const
{
	return iter;
}

void Buffer::Iterator::jump( Buffer::Size size )
{
	iter += size;
	if( iter > buffer.size() )
	{
		iter = buffer.size();
	}
}

void Buffer::Iterator::seek( Buffer::Size at )
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

