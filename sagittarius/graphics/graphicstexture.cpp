/*
 * graphicstexture.cpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#include "graphicstexture.hpp"
#include <stdgl>

namespace orion {
namespace graphics {

const uint Texture::null = GL_NULL;

Texture::Texture()
: id( null )
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
		GL_TEST_RAII;
		glGenTextures( 1 , &id );
		return true;
	}
	return false;
}

bool Texture::initialized() const
{
	return id != null;
}

void Texture::release()
{
	if( initialized() )
	{
		GL_TEST_RAII;
		glDeleteTextures( 1 , &id );
		id = null;
	}
}

uint Texture::getID() const
{
	return id;
}

} // namespace graphics 
} // namespace orion 
