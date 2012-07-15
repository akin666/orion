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
: data( NULL ),
  mode( orion::RGBA8 )
{
}

Buffer::~Buffer()
{
}

void Buffer::setMode(orion::ColorMode mode)
{
	if( data == NULL )
	{
		return;
	}
	this->mode = mode;
}

void Buffer::setResolution(const glm::ivec2& resolution)
{
	if( data == NULL )
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
	return data;
}

bool Buffer::initialize()
{
	if( data != NULL )
	{
		return false;
	}
	// TODO
	return true;
}

bool Buffer::initialized() const
{
	return data != NULL;
}

void Buffer::release()
{
}

bool Buffer::drawRect(const glm::ivec2& position, const Buffer& other)
{
	// TODO
	return false;
}

bool Buffer::drawRect(const glm::ivec2& position, const glm::ivec2& rect, void* pixeldata)
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
