/*
 * buffer.cpp
 *
 *  Created on: 16.7.2012
 *      Author: akin
 */

#include "softimagebuffer.hpp"
#include <string.h>

namespace simg
{

Buffer::Buffer()
: buffer( NULL ),
  realbuffer( NULL ),
  mode( orion::RGBA8 ),
  bytespp( 0 )
{
}

Buffer::~Buffer()
{
	release();
}

void Buffer::setMode(orion::ColorMode mode)
{
	if( buffer == NULL )
	{
		return;
	}
	this->mode = mode;
}

void Buffer::setResolution(const glm::ivec2& resolution)
{
	if( buffer == NULL )
	{
		return;
	}
	this->resolution = resolution;
}

orion::ColorMode Buffer::getMode() const
{
	return mode;
}

glm::ivec2 Buffer::getResolution() const
{
	return resolution;
}

void* Buffer::access() const
{
	return buffer;
}

bool Buffer::initialize()
{
	if( buffer != NULL )
	{
		return false;
	}
	bytespp = getByteSize( mode );

	totalSize = bytespp * resolution.x * resolution.y;

	if( totalSize < 1 )
	{
		return false;
	}

	int rtotal = totalSize + 3;
	realbuffer = new int8[ rtotal ];

	// 4 byte alignment.
	buffer = realbuffer + (((int)realbuffer)%4);

	return true;
}

bool Buffer::initialized() const
{
	return buffer != NULL;
}

void Buffer::release()
{
	delete[] realbuffer;
	buffer = realbuffer = NULL;
	bytespp = 0;
}

bool Buffer::drawRect(const glm::ivec2& position, const Buffer& other)
{
	// All variables ok?
	if( other.mode != mode || buffer == NULL )
	{
		return false;
	}
	// outside the buffer area.
	glm::ivec2 position2( position + other.resolution );
	if( position.x >= resolution.x || position.y >= resolution.y || position2.x <= 0 || position2.y <= 0 )
	{
		return true;
	}

	// 1
	glm::ivec2 dstOffset( position.x > 0 ?  position.x : 0 , position.y > 0 ?  position.y : 0 );
	glm::ivec2 srcOffset( position.x < 0 ? -position.x : 0 , position.y < 0 ? -position.y : 0 );
	glm::ivec2 area( resolution.x < position2.x ? resolution.x - position.x : position2.x - position.x , resolution.y < position2.y ? resolution.y - position.y : position2.y - position.y );

	// Simple memcpy case.
	if( position.x == 0 && resolution.y == other.resolution.y )
	{
		// calculate offsets
		int cpsize = area.y * area.x * bytespp;
		int srcoff = srcOffset.y * bytespp;
		int dstoff = dstOffset.y * bytespp;

		// memcpy!
		::memcpy( buffer + dstoff , other.buffer + srcoff , cpsize );
		return true;
	}

	return false;
}

bool Buffer::drawRect(const glm::ivec2& position, const glm::ivec2& rect, void* pixelbuffer)
{
	// TODO
	return false;
}

bool Buffer::drawRect(const glm::ivec2& min, const glm::ivec2& max, const void* pixel)
{
	// TODO
	return false;
}

bool Buffer::drawLine(const glm::ivec2& p1, const glm::ivec2& p2, const void* pixel)
{
	// TODO
	return false;
}

} // namespace simg
