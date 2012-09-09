/*
 * Buffer.cpp
 *
 *  Created on: 9.9.2012
 *      Author: akin
 */

#include "buffer.hpp"

namespace orion {

Buffer::Buffer( uint8 *data , uint length )
: at(0),
  length( length ),
  data( data )
{
}

uint8 *Buffer::access( uint offset )
{
	return data + offset;
}

uint8 *Buffer::access()
{
	return data + at;
}

void Buffer::seek( uint to )
{
	at = to;
}

uint Buffer::tell() const
{
	return at;
}

uint Buffer::max() const
{
	return length;
}

uint Buffer::size() const
{
	return length - at;
}

} // orion
