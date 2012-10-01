/*
 * simgdraw.cpp
 *
 *  Created on: 30.9.2012
 *      Author: akin
 */

#include "simgdraw.hpp"

namespace simg
{

Draw::Draw( const glm::ivec2& resolution , Color::Type mode , mbuf::Iterator& iterator )
: resolution( resolution )
, mode( mode )
, iterator( iterator )
{
}

Draw::~Draw()
{
}

void Draw::draw( const glm::ivec2& position , const glm::ivec2& res , mbuf::Iterator iterator )
{
	size_t bytespp = getByteSize( mode );

	// Simple out of bounds
	if( position.x < -res.x || position.x > resolution.x || position.y < -res.y || position.y > resolution.y )
	{
		return;
	}

	// simple fast case where width is equal. and no offsets X.
	if( res.x == resolution.x && position.x == 0 )
	{
		size_t begin = bytespp * ( position.y * res.x);
		int lasty = res.y + position.y;
		size_t size = bytespp * ((lasty < resolution.y ? lasty : resolution.y) * res.x);

		// memcpy!
		::memcpy( this->iterator.data<int8>( begin , size ) , iterator.data<int8>( 0 , size ) , size );
		return;
	}

	glm::ivec2 target_begin( position.x < 0 ? 0 : position.x , position.y < 0 ? 0 : position.y );
	glm::ivec2 source_begin( position.x < 0 ? -position.x : 0 , position.y < 0 ? -position.y : 0 );

	glm::ivec2 target_max( position.x + res.x , position.y + res.y );

	glm::ivec2 copy_size( target_begin - target_max );

	// Per scanline copying..
	size_t srcoff = (((source_begin.y * res.x) + source_begin.x) * bytespp);
	size_t dstoff = (((target_begin.y * resolution.x) + target_begin.x) * bytespp);
	int8 *src = iterator.data<int8>( srcoff , ((copy_size.y - 1) * res.x) + copy_size.x ); // this calc is wrong!! TODO , maybe one Y too much.
	int8 *dst = this->iterator.data<int8>( dstoff , ((copy_size.y - 1) * resolution.x) + copy_size.x );

	size_t cpsize = copy_size.x * bytespp;
	int dstjmp = resolution.x * bytespp;
	int srcjmp = res.x * bytespp;

	for( int i = 0 ; i < copy_size.y ; ++i )
	{
		// memcpy!
		::memcpy( dst , src , cpsize );
		dst+=dstjmp;
		src+=srcjmp;
	}
}

} // namespace simg
