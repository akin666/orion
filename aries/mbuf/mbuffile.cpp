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
: path( path )
, filesize(filesize)
, fd( -1 )
, data( NULL )
, mode( CLOSED )
{
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

bool File::open( Mode mode )
{
	int flags = 0;
	switch( mode )
	{
		case READ : flags = PROT_READ; break;
		case WRITE : flags = PROT_WRITE; break;
		case READWRITE : flags = PROT_READ | PROT_WRITE; break;
		default : return false;
	}

	this->mode = mode;
	fd = ::open( path.c_str() , flags );
	data = mmap( 0 , filesize, flags , MAP_SHARED, fd , 0 );

	if( data == MAP_FAILED )
	{
		::close( fd );
		return false;
	}
	return true;
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

bool File::ok() const
{
	return ( data != NULL ) && filesize > 0 && ( fd != -1 );
}

Buffer::Mode File::getMode() const
{
	return mode;
}

} // namespace mmap
