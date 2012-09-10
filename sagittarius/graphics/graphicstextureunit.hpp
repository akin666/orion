/*
 * graphicstextureunit.hpp
 *
 *  Created on: 14.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSTEXTUREUNIT_HPP_
#define GRAPHICSTEXTUREUNIT_HPP_

#include <graphics/graphicstexture.hpp>

namespace orion {
namespace graphics {

#ifndef GRAPHICS_TEXTURE_UNITS
# define GRAPHICS_TEXTURE_UNITS 12
#endif

class TextureUnit
{
private:
	static TextureUnit units[GRAPHICS_TEXTURE_UNITS];
	static uint idat;
	static uint generateID();
	uint id;
public:
	TextureUnit();
	~TextureUnit();

	static TextureUnit& access( int id );
	static int max();

	void bind( const Texture& texture );
	void unbind();

	uint getID() const;
};

} // namespace graphics 
} // namespace orion 
#endif // GRAPHICSTEXTUREUNIT_HPP_ 
