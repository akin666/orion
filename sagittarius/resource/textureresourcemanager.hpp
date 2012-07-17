/*
 * textureresourcemanager.hpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#ifndef TEXTURERESOURCEMANAGER_HPP_
#define TEXTURERESOURCEMANAGER_HPP_

#include <resource/resourcemanager.hpp>
#include "textureresource.hpp"
#include <tmap>

namespace orion {

class TextureResourceManager : ResourceManager<TextureResource>
{
protected:
	TMap< ResourceID , TextureResource* > resources;
public:
	TextureResourceManager();
	virtual ~TextureResourceManager();

	virtual bool has( const ResourceID& ident );
	virtual void load( const ResourceID& ident , const string8& path );
	virtual void unload( const ResourceID& ident );
	virtual TextureResource& get( const ResourceID& ident );

	virtual void realize();
	virtual void unrealize();
	virtual void unbuffer();
};

} // namespace orion 
#endif // TEXTURERESOURCEMANAGER_HPP_ 
