/*
 * textureresource.hpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#ifndef TEXTURERESOURCE_HPP_
#define TEXTURERESOURCE_HPP_

#include <resource/resource.hpp>
#include <graphics/graphicstexture.hpp>
#include <simg>

namespace orion {

class TextureResource : public Resource
{
protected:
	graphics::Texture texture;
	simg::Buffer image;
public:
	TextureResource();
	virtual ~TextureResource();

	// send CImg -> graphics
	virtual bool realize();
	// clear graphics texture
	virtual void unrealize();
	// clear CImg data
	virtual void unbuffer();
};

} // namespace orion 
#endif // TEXTURERESOURCE_HPP_ 
