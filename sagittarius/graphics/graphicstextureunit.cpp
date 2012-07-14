/*
 * graphicstextureunit.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "graphicstextureunit.hpp"
#include <graphicslib/graphicslib.hpp>

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
	Graphics::bind( *this , texture );
}

void TextureUnit::unbind()
{
	Graphics::unbind( *this );
}

uint TextureUnit::getID() const
{
	return id;
}

} // namespace graphics 
} // namespace orion 
