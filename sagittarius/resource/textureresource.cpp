/*
 * textureresource.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "textureresource.hpp"

namespace orion
{

TextureResource::TextureResource( const ResourceID& ident , string8 path )
: Resource( ident , path )
{
}

TextureResource::~TextureResource()
{
}

bool TextureResource::realize()
{
	return false;
}

void TextureResource::unrealize()
{
}

void TextureResource::unbuffer()
{
}

graphics::Texture& TextureResource::accessTexture()
{
	return texture;
}

simg::Buffer& TextureResource::accessBuffer()
{
	return image;
}

} // namespace orion 
