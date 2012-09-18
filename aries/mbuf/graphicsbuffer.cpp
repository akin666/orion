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

// helper function for.. stuff..
int resolveResidenceUpdates( const Buffer::Residence residence , const Buffer::Interval interval )
{
	 //stream = disposable (single use)
	 //static = STATIIC
	 //dynamic = update whenever you want
	 //
	 //DRAW = Jou  GPU read cpu write stuff
	 //READ = Jou , GPU Write, CPU read
	 //COPY = Jou GPU CPU access, probably a copy in both buffs
	 //  GL_STREAM_DRAW,
	 //  GL_STREAM_READ,
	 //  GL_STREAM_COPY,
	 //  GL_STATIC_DRAW,
	 //  GL_STATIC_READ,
	 //  GL_STATIC_COPY,
	 //  GL_DYNAMIC_DRAW,
	 //  GL_DYNAMIC_READ,GPU
	 //  GL_DYNAMIC_COPY
	switch( residence ) {
		case Buffer::GPU : {
			switch( interval ) {
				case Buffer::OCCASIONALLY : {
					return GL_STREAM_DRAW;
					break;
				}
				case Buffer::ONCE : {
					return GL_STATIC_DRAW;
					break;
				}
				case Buffer::MULTI : {
					return GL_DYNAMIC_DRAW;
					break;
				}
			}
			break;
		}
		case Buffer::CPU : {
			switch( interval ) {
				case Buffer::OCCASIONALLY : {
					return GL_STREAM_READ;
					break;
				}
				case Buffer::ONCE : {
					return GL_STATIC_READ;
					break;
				}
				case Buffer::MULTI : {
					return GL_DYNAMIC_READ;
					break;
				}
			}
			break;
		}
		case Buffer::CPUGPU : {
			switch( interval ) {
				case Buffer::OCCASIONALLY : {
					return GL_STREAM_COPY;
					break;
				}
				case Buffer::ONCE : {
					return GL_STATIC_COPY;
					break;
				}
				case Buffer::MULTI : {
					return GL_DYNAMIC_COPY;
					break;
				}
			}
			break;
		}
	}
	return GL_DYNAMIC_COPY;
}

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
: id(GL_NULL),
  bsize(0),
  mode( CLOSED )
{
}

Buffer::~Buffer()
{
	if( id != GL_NULL )
	{
		GL_TEST_RAII;
		glDeleteBuffers( 1 , &id );
		id = GL_NULL;
	}
}

void Buffer::initialize( std::size_t size , Residence residence , Interval interval )
{
	GL_TEST_RAII;
	if( id == GL_NULL )
	{
		glGenBuffers( 1 , &id );
	}

	int hint = resolveResidenceUpdates( residence , interval );
	int bindStyle = resolveBindStyle( WRITE );

	glBindBuffer( bindStyle , id );
	glBufferData( bindStyle , size , NULL , hint );
	glBindBuffer( bindStyle , GL_NULL );
}

std::size_t Buffer::size() const
{
	return bsize;
}

void *Buffer::at( std::size_t position ) const
{
	return NULL;
}

bool Buffer::open( Mode mode )
{
	GL_TEST_RAII;
	this->mode = mode;
	int bindStyle = resolveBindStyle( mode );
	glBindBuffer( bindStyle , id );

	return true;
}

void Buffer::close()
{
	GL_TEST_RAII;
	int bindStyle = resolveBindStyle( mode );
	glBindBuffer( bindStyle , GL_NULL );
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
