/*
 * mmapbuffer.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mmapbuffer.hpp"

namespace mmap {

Buffer::Iterator::Iterator( const Iterator& other )
: buffer( other.buffer ),
  iter( other.iter )
{
}

Buffer::Iterator::Iterator( Buffer& buffer , Size& at )
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

void *Buffer::Iterator::end() const
{
	return buffer.end();
}

Buffer::Iterator Buffer::begin() const
{
	return Iterator( *this , 0 );
}

Buffer::Iterator Buffer::end() const
{
	return Iterator( *this , size() );
}

} // namespace mmap

