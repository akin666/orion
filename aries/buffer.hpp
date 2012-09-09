/*
 * buffer.hpp
 *
 *  Created on: 9.9.2012
 *      Author: akin
 */

#ifndef BUFFER_BUFFER_HPP_
#define BUFFER_BUFFER_HPP_

#include <orion>
#include <cstring>

namespace orion {

class Buffer
{
protected:
	uint at;
	uint length;
	uint8 *data;
public:
	Buffer( uint8 *data , uint length );

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
		std::memcpy( (void*)target , (void*)(data + at) , sizeof(size) );
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
		std::memcpy( (void*)target , (void*)(data + at) , sizeof(size) );
		return true;
	}

	template <class CType>
	CType *access( uint offset )
	{
		return (CType *)(access(offset));
	}

	template <class CType>
	CType *access()
	{
		return (CType *)(access());
	}

	uint8 *access( uint offset );
	uint8 *access();
	void seek( uint to );
	uint tell() const;
	uint max() const;
	uint size() const;
};

} // orion

#endif // BUFFER_BUFFER_HPP_
