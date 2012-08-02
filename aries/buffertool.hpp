/*
 * BufferTool.hpp
 *
 *  Created on: 31.7.2012
 *      Author: akin
 */

#ifndef BUFFERTOOL_HPP_
#define BUFFERTOOL_HPP_

#include <orion>
#include <cstring>

namespace orion
{

class BufferTool
{
protected:
	uint at;
	uint length;
	const uint8 *data;
public:
	BufferTool( const uint8 *data , uint length )
	: at(0),
	  length( length ),
	  data( data )
	{
	}

	template <class CType>
	bool read( CType *target , int count = 1 )
	{
		int size = sizeof( CType ) * count;
		if( at + size > length )
		{
			return false;
		}
		// Warning.. but..
		// To make it no warning, would need to cast to INT or LONG, depending on platform.
		// To create such structure and macros, for multiplatform compatibility,
		// would be engineering and 'complicators gloves' pissing contest,
		// It gives out a warning, DEAL WITH IT.
		std::memcpy( (void*)target , (const void*)(data + at) , sizeof(size) );
		at += size;
		return true;
	}

	template <class CType>
	bool readAt( CType *target , uint at , int count = 1 )
	{
		int size = sizeof( CType ) * count;
		if( at + size > length )
		{
			return false;
		}
		// Warning.. but..
		// To make it no warning, would need to cast to INT or LONG, depending on platform.
		// To create such structure and macros, for multiplatform compatibility,
		// would be engineering and 'complicators gloves' pissing contest,
		// It gives out a warning, DEAL WITH IT.
		std::memcpy( (void*)target , (const void*)(data + at) , sizeof(size) );
		return true;
	}

	const uint8 *access( uint offset )
	{
		return data + offset;
	}

	void seek( uint to )
	{
		at = to;
	}

	uint tell()
	{
		return at;
	}

	uint max()
	{
		return length;
	}

	uint size()
	{
		return length - at;
	}
};

} // namespace orion 
#endif // BUFFERTOOL_HPP_
