/*
 * rendertarget.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include <video/videomode.hpp>

namespace orion {

class RenderTarget
{
protected:
	VideoMode mode;
public:
	RenderTarget();
	RenderTarget( const VideoMode& mode );
	virtual ~RenderTarget();

	VideoMode& getVideoMode();

	virtual void bind();
};

} // namespace orion
#endif // RENDERTARGET_HPP_
