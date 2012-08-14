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

	std::vector<iqmtriangle> triangles;
	std::vector<iqmmesh> meshes;
	std::vector<iqmjoint> joints;
	std::vector<iqmtriangle> adjacencyTriangles;

//	std::memset( &textures[0] , 0, meshCount * sizeof(uint32) );

	typedef std::vector<iqmvertexarray> VertexArraySet;
	VertexArraySet vertexArrays;
	vertexArrays.resize( header.num_vertexarrays );
	buffer.readAt( &vertexArrays[0] , header.ofs_vertexarrays , header.num_vertexarrays );

	positions.resize( vertexCount );
	normals.resize( vertexCount );
	tangents.resize( vertexCount );
	texCoords.resize( vertexCount );
	blendIndexes.resize( vertexCount );
	blendWeights.resize( vertexCount );

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

	triangles.resize( triangleCount );
	meshes.resize( meshCount );
	joints.resize( jointCount );

	buffer.readAt( &triangles[0] , header.ofs_triangles , triangleCount );
	buffer.readAt( &meshes[0] , header.ofs_meshes , meshCount );
	buffer.readAt( &joints[0] , header.ofs_joints , jointCount );

	if( adjacencyOffset != 0 )
	{
		adjacencyTriangles.resize( triangleCount );
		buffer.readAt( &adjacencyTriangles[0] , adjacencyOffset , triangleCount );
	}

//    baseframe = new Matrix3x4[hdr.num_joints];
//    inversebaseframe = new Matrix3x4[hdr.num_joints];
//    for(int i = 0; i < (int)hdr.num_joints; i++)
//    {
//        iqmjoint &j = joints[i];
//        baseframe[i] = Matrix3x4(Quat(j.rotate).normalize(), Vec3(j.translate), Vec3(j.scale));
//        inversebaseframe[i].invert(baseframe[i]);
//        if(j.parent >= 0)
//        {
//            baseframe[i] = baseframe[j.parent] * baseframe[i];
//            inversebaseframe[i] *= inversebaseframe[j.parent];
//        }
//    }

//    for(int i = 0; i < (int)hdr.num_meshes; i++)
//    {
//        iqmmesh &m = meshes[i];
//        printf("%s: loaded mesh: %s\n", filename, &str[m.name]);
//        textures[i] = loadtexture(&str[m.material], 0);
//        if(textures[i]) printf("%s: loaded material: %s\n", filename, &str[m.material]);
//    }

    if( header.num_poses != jointCount)
    {
    	return false;
    }

    // No animations?
    if( header.num_anims < 1 )
    {
    	return true;
    }

	std::vector<iqmpose> poses;
	std::vector<iqmanim> anims;
	poses.resize( header.num_poses );
	anims.resize( header.num_anims );
	buffer.readAt( &poses[0] , header.ofs_poses , header.num_poses );//    lilswap((uint *)&buf[hdr.ofs_poses], hdr.num_poses*sizeof(iqmpose)/sizeof(uint));
	buffer.readAt( &anims[0] , header.ofs_anims , header.num_anims );//    lilswap((uint *)&buf[hdr.ofs_anims], hdr.num_anims*sizeof(iqmanim)/sizeof(uint));

//    lilswap((ushort *)&buf[hdr.ofs_frames], hdr.num_frames*hdr.num_framechannels);
//    if(hdr.ofs_bounds) lilswap((uint *)&buf[hdr.ofs_bounds], hdr.num_frames*sizeof(iqmbounds)/sizeof(uint));
//
//    animdata = buf;
//    numanims = hdr.num_anims;
//    numframes = hdr.num_frames;
//
//    const char *str = hdr.ofs_text ? (char *)&buf[hdr.ofs_text] : "";
//    anims = (iqmanim *)&buf[hdr.ofs_anims];
//    poses = (iqmpose *)&buf[hdr.ofs_poses];
//    frames = new Matrix3x4[hdr.num_frames * hdr.num_poses];
//    ushort *framedata = (ushort *)&buf[hdr.ofs_frames];
//    if(hdr.ofs_bounds) bounds = (iqmbounds *)&buf[hdr.ofs_bounds];
//
//    for(int i = 0; i < (int)hdr.num_frames; i++)
//    {
//        for(int j = 0; j < (int)hdr.num_poses; j++)
//        {
//            iqmpose &p = poses[j];
//            Quat rotate;
//            Vec3 translate, scale;
//            translate.x = p.channeloffset[0]; if(p.mask&0x01) translate.x += *framedata++ * p.channelscale[0];
//            translate.y = p.channeloffset[1]; if(p.mask&0x02) translate.y += *framedata++ * p.channelscale[1];
//            translate.z = p.channeloffset[2]; if(p.mask&0x04) translate.z += *framedata++ * p.channelscale[2];
//            rotate.x = p.channeloffset[3]; if(p.mask&0x08) rotate.x += *framedata++ * p.channelscale[3];
//            rotate.y = p.channeloffset[4]; if(p.mask&0x10) rotate.y += *framedata++ * p.channelscale[4];
//            rotate.z = p.channeloffset[5]; if(p.mask&0x20) rotate.z += *framedata++ * p.channelscale[5];
//            rotate.w = p.channeloffset[6]; if(p.mask&0x40) rotate.w += *framedata++ * p.channelscale[6];
//            scale.x = p.channeloffset[7]; if(p.mask&0x80) scale.x += *framedata++ * p.channelscale[7];
//            scale.y = p.channeloffset[8]; if(p.mask&0x100) scale.y += *framedata++ * p.channelscale[8];
//            scale.z = p.channeloffset[9]; if(p.mask&0x200) scale.z += *framedata++ * p.channelscale[9];
//            // Concatenate each pose with the inverse base pose to avoid doing this at animation time.
//            // If the joint has a parent, then it needs to be pre-concatenated with its parent's base pose.
//            // Thus it all negates at animation time like so:
//            //   (parentPose * parentInverseBasePose) * (parentBasePose * childPose * childInverseBasePose) =>
//            //   parentPose * (parentInverseBasePose * parentBasePose) * childPose * childInverseBasePose =>
//            //   parentPose * childPose * childInverseBasePose
//            Matrix3x4 m(rotate.normalize(), translate, scale);
//            if(p.parent >= 0) frames[i*hdr.num_poses + j] = baseframe[p.parent] * m * inversebaseframe[j];
//            else frames[i*hdr.num_poses + j] = m * inversebaseframe[j];
//        }
//    }
//
//    for(int i = 0; i < (int)hdr.num_anims; i++)
//    {
//        iqmanim &a = anims[i];
//        printf("%s: loaded anim: %s\n", filename, &str[a.name]);
//    }

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

	return true;
}

} // namespace orion 
