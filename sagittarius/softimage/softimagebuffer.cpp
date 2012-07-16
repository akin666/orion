/*
 * buffer.cpp
 *
 *  Created on: 16.7.2012
 *      Author: akin
 */

#include "softimagebuffer.hpp"

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

	int total = bytespp * resolution.x * resolution.y;

	if( total < 1 )
	{
		return false;
	}

	int rtotal = total + 3;
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
	// TODO
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
