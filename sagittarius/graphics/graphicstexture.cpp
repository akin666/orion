/*
 * graphicstexture.cpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#include "graphicstexture.hpp"
#include <graphicslib/graphicslib.hpp>

namespace orion {
namespace graphics {

Texture::Texture()
: id( Graphics::NotInitialized )
{
}

Texture::~Texture()
{
	release();
}

bool Texture::initialize()
{
	if( !initialized() )
	{
		Graphics::generateTextureID( 1 , &id );

		return true;
	}
	return false;
}

bool Texture::initialized() const
{
	return id != Graphics::NotInitialized;
}

void Texture::release()
{
	if( initialized() )
	{
		Graphics::releaseTextureID( 1 , &id );
	}
}

uint Texture::getID() const
{
	return id;
}

} // namespace graphics 
} // namespace orion 
