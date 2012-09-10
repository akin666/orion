/*
 * graphicstexture.hpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSTEXTURE_HPP_
#define GRAPHICSTEXTURE_HPP_

#include <orion>

namespace orion {
namespace graphics {

class Texture
{
protected:
	uint id;
public:
	static const uint null;

	Texture();
	virtual ~Texture();

	bool initialize();
	bool initialized() const;
	void release();

	uint getID() const;
};

} // namespace graphics 
} // namespace orion 
#endif // GRAPHICSTEXTURE_HPP_ 
