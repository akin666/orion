/*
 * buffer.hpp
 *
 *  Created on: 16.7.2012
 *      Author: akin
 */

#ifndef SOFTIMAGE_BUFFER_HPP_
#define SOFTIMAGE_BUFFER_HPP_

#include <orion>

namespace simg
{

class Buffer
{
protected:
	void *buffer;		// does not have ownership
	void *realbuffer; 	// ownership
	int totalSize;
	orion::ColorMode mode;
	glm::ivec2 resolution;
	uint8 bytespp;
public:
	Buffer();
	// Wrap Buffer around existing buffer, does not transfer ownership.
	Buffer( const glm::ivec2& resolution , orion::ColorMode mode , void *pixelbuffer );
	virtual ~Buffer();

	void setMode( orion::ColorMode mode );
	void setResolution( const glm::ivec2& resolution );

	orion::ColorMode getMode() const;
	glm::ivec2 getResolution() const;

	void *access() const;

	bool initialize();
	bool initialized() const;
	void release();

	bool drawRect( const glm::ivec2& position , const Buffer& other );
	bool drawRect( const glm::ivec2& position , const glm::ivec2& rect , void *pixelbuffer );
	bool drawRect( const glm::ivec2& min , const glm::ivec2& max , const void *pixel );
	bool drawLine( const glm::ivec2& p1 , const glm::ivec2& p2 , const void *pixel );
};

} // namespace simg
#endif // SOFTIMAGE_BUFFER_HPP_
