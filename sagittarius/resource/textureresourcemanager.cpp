/*
 * textureresourcemanager.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "textureresourcemanager.hpp"

namespace orion
{

TextureResourceManager::TextureResourceManager()
{
}

TextureResourceManager::~TextureResourceManager()
{
}

bool TextureResourceManager::has( const string8& ident )
{
	return false;
}

void TextureResourceManager::load( const string8& ident , const string8& path )
{
}

void TextureResourceManager::unload( const string8& ident )
{
}

TextureResource& TextureResourceManager::get( const string8& ident )
{
	TextureResource tt;
	return tt;
}

void TextureResourceManager::realize()
{
}

void TextureResourceManager::unrealize()
{
}

void TextureResourceManager::unbuffer()
{
}


} // namespace orion 
