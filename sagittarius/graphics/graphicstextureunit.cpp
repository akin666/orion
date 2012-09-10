/*
 * graphicstextureunit.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "graphicstextureunit.hpp"

#include <stdgl>

namespace orion {
namespace graphics {

TextureUnit TextureUnit::units[GRAPHICS_TEXTURE_UNITS];
uint TextureUnit::idat = 0;
uint TextureUnit::generateID()
{
	return idat++;
}

TextureUnit& TextureUnit::access( int id )
{
	return units[ id % GRAPHICS_TEXTURE_UNITS ];
}

int TextureUnit::max()
{
	return GRAPHICS_TEXTURE_UNITS - 1;
}

TextureUnit::TextureUnit()
: id( generateID() )
{
}

TextureUnit::~TextureUnit()
{
}

void TextureUnit::bind( const Texture& texture )
{
	GL_TEST_RAII;
	// Bind the texture
	glActiveTexture( GL_TEXTURE0 + id );
	glBindTexture (GL_TEXTURE_2D, texture.getID() );
}

void TextureUnit::unbind()
{
	GL_TEST_RAII;
	// Bind the texture
	glActiveTexture( GL_TEXTURE0 + id );
	glBindTexture(GL_TEXTURE_2D, GL_NULL );
}

uint TextureUnit::getID() const
{
	return id;
}

} // namespace graphics 
} // namespace orion 
