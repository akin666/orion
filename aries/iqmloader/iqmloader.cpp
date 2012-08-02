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
#include <cstring>
#include <buffertool.hpp>

namespace orion
{

class Matrix3x4 {
public:
	float v[3*4];
};

class Vert2 {
public:
	float x,y;
};

class Vert3 {
public:
	float x,y,z;
};

class Vert4 {
public:
	float x,y,z,w;
};


class Vert4uc {
public:
	unsigned char x,y,z,w;
};

IQMLoader::IQMLoader()
{
}

IQMLoader::~IQMLoader()
{
}

bool loadMeshData( BufferTool& buffer , const iqmheader& header )
{
	int vertexCount = header.num_vertexes;
	int jointCount = header.num_joints;
	int meshCount = header.num_meshes;
	int triangleCount = header.num_triangles;

	uint textOffset = header.ofs_text; // 0 == No texts
	uint adjacencyOffset = header.ofs_adjacency;

	std::vector<Vert3> positions;
	std::vector<Vert3> normals;
	std::vector<Vert4> tangents;
	std::vector<Vert2> texCoords;
	std::vector<Vert4uc> blendIndexes;
	std::vector<Vert4uc> blendWeights;
	std::vector<Vert3> bitangents;
	std::vector<Matrix3x4> frames;
	std::vector<uint32> textures;

	std::vector<iqmtriangle> triangles;
	std::vector<iqmmesh> meshes;
	std::vector<iqmjoint> joints;
	std::vector<iqmtriangle> adjacencyTriangles;

	// [x,y,z],..
	positions.resize( vertexCount );
	normals.resize( vertexCount );
	tangents.resize( vertexCount );
	texCoords.resize( vertexCount );
	blendIndexes.resize( vertexCount );
	blendWeights.resize( vertexCount );
	bitangents.resize( vertexCount );
	frames.resize( jointCount );
	textures.resize( meshCount );

	triangles.resize( triangleCount );
	meshes.resize( meshCount );
	joints.resize( jointCount );
	if( adjacencyOffset != 0 )
	{
		adjacencyTriangles.resize( triangleCount );
	}

	std::memset( &textures[0] , 0, meshCount * sizeof(uint32) );

	typedef std::vector<iqmvertexarray> VertexArraySet;
	VertexArraySet vertexArrays;
	vertexArrays.resize( header.num_vertexarrays );
	buffer.readAt( &vertexArrays[0] , header.ofs_vertexarrays , header.num_vertexarrays );

	for( VertexArraySet::iterator iter = vertexArrays.begin() ; iter != vertexArrays.end() ; ++iter )
	{
		switch( iter->type )
		{
			case IQM_POSITION:
				if( iter->format != IQM_FLOAT || iter->size != 3)
				{
					return false;
				}
				buffer.readAt( &positions[0] , iter->offset , vertexCount );
				break;
			case IQM_NORMAL:
				if( iter->format != IQM_FLOAT || iter->size != 3)
				{
					return false;
				}
				buffer.readAt( &normals[0] , iter->offset , vertexCount );
				break;
			case IQM_TANGENT:
				if( iter->format != IQM_FLOAT || iter->size != 4)
				{
					return false;
				}
				buffer.readAt( &tangents[0] , iter->offset , vertexCount );
				break;
			case IQM_TEXCOORD:
				if( iter->format != IQM_FLOAT || iter->size != 2)
				{
					return false;
				}
				buffer.readAt( &texCoords[0] , iter->offset , vertexCount );
				break;
			case IQM_BLENDINDEXES:
				if( iter->format != IQM_UBYTE || iter->size != 4)
				{
					return false;
				}
				buffer.readAt( &blendIndexes[0] , iter->offset , vertexCount );
				break;
			case IQM_BLENDWEIGHTS:
				if( iter->format != IQM_UBYTE || iter->size != 4)
				{
					return false;
				}
				buffer.readAt( &blendWeights[0] , iter->offset , vertexCount );
				break;
			default:
				break;
		}
	}

	buffer.readAt( &triangles[0] , header.ofs_triangles , triangleCount );
	buffer.readAt( &meshes[0] , header.ofs_meshes , meshCount );
	buffer.readAt( &joints[0] , header.ofs_triangles , jointCount );
	if( adjacencyOffset != 0 )
	{
		buffer.readAt( &adjacencyTriangles[0] , adjacencyOffset , triangleCount );
	}


	return true;
}

bool loadAnimationData( BufferTool& buffer , const iqmheader& header )
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

    uint8 *ptr = &buffer[0];
    return load( ptr , readSize );
}

bool IQMLoader::load( const uint8 *buffer , uint32 maxlen )
{
	BufferTool buffertool( buffer , maxlen );

	// Read header.
	iqmheader header;
	if( !buffertool.read( &header ) )
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

	// Now we have a buffer.. and the header..
	if( header.num_meshes > 0 )
	{
		if( !loadMeshData( buffertool , header ) )
		{
			return false;
		}
	}
	if( header.num_anims > 0 )
	{
		if( !loadAnimationData( buffertool , header ) )
		{
			return false;
		}
	}
	return true;
}

} // namespace orion 
