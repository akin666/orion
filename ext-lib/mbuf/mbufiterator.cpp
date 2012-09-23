/*
 * mbufiterator.cpp
 *
 *  Created on: 19.9.2012
 *      Author: akin
 */

#include "mbufiterator.hpp"
#include "mbufbuffer.hpp"
#include <cassert>

namespace mbuf
{

void *Iterator::retain( std::size_t it , std::size_t count )
{
	release();
	datas = buffer.retain( it , count );
	return datas;
}

void Iterator::release()
{
	if( datas != NULL )
	{
		buffer.release( datas );
		datas = NULL;
	}
}

Iterator::Iterator( const Iterator& other )
: buffer( other.buffer )
, iter( other.iter )
, datas( NULL )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
	++buffer.ref_count;
}

Iterator::Iterator( Buffer& buffer , std::size_t at )
: buffer( buffer )
, iter( at )
, datas( NULL )
{
	if( !buffer.ok() )
	{
		assert( false );
	}
	++buffer.ref_count;
}

Iterator::~Iterator()
{
	release();
	--buffer.ref_count;
}

std::size_t Iterator::size() const
{
	return buffer.size();
}

std::size_t Iterator::position() const
{
	return iter;
}

std::size_t Iterator::remaining() const
{
	return buffer.size() - iter;
}

void Iterator::jump( std::size_t size )
{
	iter += size;
	if( iter > buffer.size() )
	{
		iter = buffer.size();
	}
}

void Iterator::seek( std::size_t at )
{
	iter = at;
}

bool Iterator::finished() const
{
	return iter >= buffer.size();
}

void Iterator::reset()
{
	release();
	iter = 0;
}

} // namespace mbuf
