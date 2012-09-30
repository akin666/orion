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
: buffer( NULL )
, realbuffer( NULL )
, totalSize( 0 )
, mode( Color::RGBA8 )
, bytespp( 0 )
, iterator( NULL )
{
}

Buffer::Buffer( const glm::ivec2& resolution , Color::Type mode , void *pixelbuffer )
: buffer( (int8*)pixelbuffer )
, realbuffer( NULL )
, totalSize( 0 )
, mode( mode )
, resolution( resolution )
, bytespp( getByteSize( mode ) )
, iterator( NULL )
{
	totalSize = bytespp * resolution.x * resolution.y;
}

Buffer::Buffer( const glm::ivec2& resolution , Color::Type mode , mbuf::Buffer& pixelbuffer )
: buffer( NULL )
, realbuffer( NULL )
, totalSize( 0 )
, mode( mode )
, resolution( resolution )
, bytespp( getByteSize( mode ) )
, iterator( NULL )
{
	// We need readwrite access!
	if( (pixelbuffer.getMode() & mbuf::Buffer::READWRITE) != mbuf::Buffer::READWRITE )
	{
		if( !pixelbuffer.open( mbuf::Buffer::READWRITE ) )
		{
			// ERROR! could not open the requested mode!
			throw "";
		}
	}

	// Open etc with pixelbuffer.. init et al.
	totalSize = bytespp * resolution.x * resolution.y;

	iterator = new mbuf::Iterator( pixelbuffer.begin() );
	buffer = iterator->data<int8>( 0  , totalSize );
}

Buffer::~Buffer()
{
	release();
}

void Buffer::setMode(Color::Type mode)
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

Color::Type Buffer::getMode() const
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
	buffer = realbuffer + (((long)realbuffer)%4);

	// reset the buffer to 0s
	::memset( buffer , 0x0 , totalSize );

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

	delete iterator;
	iterator = NULL;
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

	// scanline at a time copying
	int cpsize = area.x * bytespp;
	int dstjmp = resolution.x * bytespp;
	int srcjmp = other.resolution.x * bytespp;

	void *src = (((srcOffset.y * other.resolution.x) + srcOffset.x) * bytespp) + other.buffer;
	void *dst = (((dstOffset.y * resolution.x) + dstOffset.x) * bytespp) + buffer;
	for( int i = 0 ; i < area.y ; ++i )
	{
		// memcpy!
		::memcpy( dst , src , cpsize );
		dst+=dstjmp;
		src+=srcjmp;
	}

	return true;
}

bool Buffer::drawRect(const glm::ivec2& position, const glm::ivec2& rect, void* pixelbuffer)
{
	Buffer buf( rect , mode , pixelbuffer );
	return drawRect( position, buf );
}

bool Buffer::drawRect(const glm::ivec2& min, const glm::ivec2& max, const void* pixel)
{
	glm::ivec2 rmin( min.x < max.x ? min.x : max.x , min.y < max.y ? min.y : max.y );
	glm::ivec2 rmax( min.x > max.x ? min.x : max.x , min.y > max.y ? min.y : max.y );

	// normalize to real coordinates..
	rmin.x = rmin.x < 0 ? 0 : rmin.x;
	rmin.y = rmin.y < 0 ? 0 : rmin.y;
	rmax.x = rmax.x > resolution.x ? resolution.x : rmax.x;
	rmax.y = rmax.y > resolution.y ? resolution.y : rmax.y;

	glm::ivec2 area( rmax.x - rmin.x , rmax.y - rmin.y );

	// copy one line..
	void *dst = buffer + (((rmin.y * resolution.x) + rmin.x ) * bytespp);
	void *origin = dst;
	for( int i = 0 ; i < rmax.x ; ++i )
	{
		::memcpy( dst , pixel , bytespp );
		dst += bytespp;
	}

	int jmpsize = resolution.x * bytespp;
	int cpsize = area.x * bytespp;
	dst = origin + jmpsize;
	// copy the line, n-1 times..
	for( int i = 1 ; i < area.y ; ++i )
	{
		::memcpy( dst , origin , cpsize );
		dst += jmpsize;
	}

	return true;
}

bool Buffer::drawLine(const glm::ivec2& p1, const glm::ivec2& p2, const void* pixel)
{
	// TODO
	return false;
}

} // namespace simg
