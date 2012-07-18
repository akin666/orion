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

bool TextureResourceManager::has( const ResourceID& ident )
{
	return resources.has( ident );
}

void TextureResourceManager::load( const ResourceID& ident , const string8& path )
{
	std::lock_guard<std::mutex> lock(mutex);
	if( resources.has( ident ) )
	{
		return;
	}

	TextureResource *res = new TextureResource( ident , path );
	resources[ ident ] = res;

	work.add( res );
}

void TextureResourceManager::unload( const ResourceID& ident )
{
	std::lock_guard<std::mutex> lock(mutex);
	TextureResource *res = resources.pop( ident );
	if( res == NULL )
	{
		return;
	}

	delete res;
}

TextureResource& TextureResourceManager::get( const ResourceID& ident )
{
	return *(resources[ ident ]);
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
