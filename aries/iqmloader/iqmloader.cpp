/*
 * iqmloader.cpp
 *
 *  Created on: 26.7.2012
 *      Author: akin
 */

#include "iqmloader.hpp"
#include <iqm>
#include <iostream>
#include <fstream>
#include <cmath>

namespace orion
{

IQMLoader::IQMLoader()
{
}

IQMLoader::~IQMLoader()
{
}

bool loadMeshData( uint8 *buffer , const iqmheader& header )
{
	return true;
}

bool loadAnimationData( uint8 *buffer , const iqmheader& header )
{
	return true;
}

bool IQMLoader::load( const std::string& path )
{
	std::ifstream stream;
	stream.open( path.c_str() );

	// Read header.
    iqmheader header;
    stream.read( (char*)&header, sizeof(iqmheader) );
    if( stream.gcount() != sizeof(iqmheader) )
    {
    	return false;
    }
    stream.seekg( 0 ); // back to the beginning

    int readSize = header.filesize;
    std::vector<uint8> buffer;
    buffer.resize( readSize );
    stream.read( (char*)&buffer[0] , readSize );
    if( stream.gcount() != readSize )
    {
    	return false;
    }
    stream.close();

    return load( &buffer[0] , readSize );
}

bool IQMLoader::load( const uint8 *buffer , uint32 maxlen )
{
	// Read header.
	iqmheader header;
	stream.read( (char*)&header, sizeof(iqmheader) );
	if( stream.gcount() != sizeof(iqmheader) )
	{
		return false;
	}

	// Validate header.
	if(
		header.version != IQM_VERSION ||	// version.
		header.filesize > (16<<20)			// 16Mb max.. not specified in specs.. but 16Megs is a lot..
		)
	{
		return false;
	}

	int readSize = header.filesize - sizeof(header);
	std::vector<uint8> buffer;
	buffer.resize( readSize );
	stream.read( (char*)&buffer[0] , readSize );
	if( stream.gcount() != readSize )
	{
		return false;
	}
	stream.close();

	// Now we have a buffer.. and the header..
	if( header.num_meshes > 0 )
	{
		if( !loadMeshData( &buffer[0] , header ) ) return false;
	}
	if( header.num_anims > 0 )
	{
		if( !loadAnimationData( &buffer[0] , header ) ) return false;
	}
	return true;
}

} // namespace orion 
