/*
 * textureresourcemanager.cpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#include "textureresourcemanager.hpp"
#include <threadpool>

namespace orion
{

TextureResourceManager::TextureResourceManager()
{
}

TextureResourceManager::~TextureResourceManager()
{
}

bool TextureResourceManager::has( const ResourceID& ident )
{
	return false;
}

void TextureResourceManager::load( const ResourceID& ident , const string8& path )
{
	// Command work to load the resource.
	// If already running, no need to re-add to work que.
	// If no running, then needs to be added to work que.
	queWork( work );
}

void TextureResourceManager::unload( const ResourceID& ident )
{
}

TextureResource& TextureResourceManager::get( const ResourceID& ident )
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
