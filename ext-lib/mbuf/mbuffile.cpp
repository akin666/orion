/*
 * mmapfile.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbuffile.hpp"
#include <iostream>

#include "mman"
#include <sys/stat.h>

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

File& File::setFile( const std::string& path )
{
	if( mode == CLOSED )
	{
		this->path = path;
	}
	return *this;
}

File& File::setSize( std::size_t filesize )
{
	if( mode == CLOSED )
	{
		this->filesize = filesize;
	}
	return *this;
}

std::size_t File::size() const
{
	return filesize;
}

void *File::retain( std::size_t position , std::size_t count )
{
	return (void*)((long)data + position);
}

void File::release( void *buffer )
{
}

bool File::open( Mode mode )
{
	bool nocreate = (mode & NO_CREATE) != 0;
	bool read = (mode & READ) != 0;
	bool write = (mode & WRITE) != 0;

	int flags = 0;
	if( read ) flags |= PROT_READ;
	if( write ) flags |= PROT_WRITE;

	if( nocreate )
	{
		struct stat st;
		if( stat(path.c_str(), &st) == 0 )
		{
			filesize = st.st_size;
		}
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

    mode = CLOSED;
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
