/*
 * mmapfile.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbuffile.hpp"
#include <iostream>

#include <mman>

#include <cassert>

namespace mbuf
{

File::File( const std::string& path , std::size_t filesize )
: filesize(filesize)
{
	fd = open( path.c_str() , PROT_READ | PROT_WRITE );
	data = mmap( 0 , filesize, PROT_READ, MAP_SHARED, fd , 0 );

	if (data == MAP_FAILED)
	{
		::close( fd );
		assert( false );
	}
}

File::~File()
{
	close();
}

std::size_t File::size() const
{
	return filesize;
}

void *File::at( std::size_t position ) const
{
	return (void*)((long)data + position);
}

void File::close()
{
	if( fd == -1 )
	{
		return;
	}
    if( munmap( data , filesize ) == -1)
    {
		assert( false );
    }

    ::close( fd );
    fd = -1;
}

bool File::ok()
{
	return ( data != NULL ) && filesize > 0 && ( fd != -1 );
}

} // namespace mmap
