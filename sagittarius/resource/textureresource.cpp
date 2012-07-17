/*
 * textureresource.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "textureresource.hpp"

namespace orion
{

TextureResource::TextureResource()
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
