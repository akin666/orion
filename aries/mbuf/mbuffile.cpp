/*
 * mmapfile.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbuffile.hpp"
#include <iostream>

#include <mman>

namespace mbuf
{

File::File( const std::string& path , int filesize )
: filesize(filesize)
{
	fd = open( path.c_str() , PROT_READ | PROT_WRITE );
	data = mmap( 0 , filesize, PROT_READ, MAP_SHARED, fd , 0 );

	if (data == MAP_FAILED)
	{
		::close( fd );
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}
}

File::~File()
{
	close();
}

File::Size File::size() const
{
	return filesize;
}

void *File::at( File::Size position ) const
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
    	perror("Error un-mmapping the file");
    }

    ::close( fd );
    fd = -1;
}

bool File::ok()
{
	return ( data != NULL ) && filesize > 0 && ( fd != -1 );
}

} // namespace mmap
