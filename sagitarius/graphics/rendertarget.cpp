/*
 * rendertarget.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "rendertarget.hpp"

namespace orion {

RenderTarget::RenderTarget()
{
}

RenderTarget::RenderTarget( const VideoMode& mode )
: mode( mode )
{
}

RenderTarget::~RenderTarget()
{
}

VideoMode& RenderTarget::getVideoMode()
{
	return mode;
}

void RenderTarget::bind()
{
}

} // namespace orion
