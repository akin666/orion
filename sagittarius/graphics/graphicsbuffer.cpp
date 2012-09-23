/*
 * graphicsbuffer.cpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#include "graphicsbuffer.hpp"
#include <stdgl>

namespace orion {
namespace graphics {

int resolveBindStyle( Buffer::Mode mode )
{
	switch( mode )
	{
		case Buffer::WRITE : return GL_PIXEL_PACK_BUFFER; break;
		case Buffer::READ :  return GL_PIXEL_UNPACK_BUFFER; break;
//		case Buffer::arrayBuffer : bindStyle = 			GL_ARRAY_BUFFER; break;
//		case Buffer::elementArrayBuffer : bindStyle=	GL_ELEMENT_ARRAY_BUFFER; break;
		default : break;// : bindStyle = 							GL_PIXEL_PACK_BUFFER; break;
	}
	return GL_PIXEL_PACK_BUFFER;
}

Buffer::Buffer()
: id(GL_NULL)
, bsize(0)
, mode( CLOSED )
, ptr( NULL )
{
}

Buffer::~Buffer()
{
	if( mode != CLOSED )
	{
		close();
	}
}

void Buffer::initialize( unsigned int id )
{
	this->id = id;
}

std::size_t Buffer::size() const
{
	return bsize;
}

void *Buffer::retain( std::size_t position , std::size_t count )
{
	if( ptr == NULL )
	{
		return NULL;
	}

	return (void*)((long)ptr + position);
}

void Buffer::release( void *buffer )
{
}

bool Buffer::open( Mode mode )
{
	if( mode != READ && mode != WRITE )
	{
		return false;
	}

	GL_TEST_RAII;
	this->mode = mode;
	int bindStyle = resolveBindStyle( mode );
	glBindBuffer( bindStyle , id );

	int buffstyle;
	switch( mode )
	{
		case READ : buffstyle = GL_READ_ONLY; break;
		case WRITE : buffstyle = GL_WRITE_ONLY; break;
		case READWRITE : buffstyle = GL_READ_WRITE; break;
		default: return false;
	}

	ptr = (void*)glMapBufferARB( bindStyle , buffstyle );

	return true;
}

void Buffer::close()
{
	GL_TEST_RAII;
	int bindStyle = resolveBindStyle( mode );
	glUnmapBuffer( bindStyle );
	glBindBuffer( bindStyle , GL_NULL );
	ptr = NULL;
}

bool Buffer::ok() const
{
	return id != GL_NULL;
}

Buffer::Mode Buffer::getMode() const
{
	return mode;
}

} // namespace graphics 
} // namespace orion 
