/*
 * rendertarget.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "rendertarget.hpp"

namespace orion {
namespace graphics {

RenderTarget::RenderTarget()
{
}

RenderTarget::RenderTarget( const RenderTargetSetting& mode )
: mode( mode )
{
}

RenderTarget::~RenderTarget()
{
}

RenderTargetSetting& RenderTarget::getVideoMode()
{
	return mode;
}

void RenderTarget::bind()
{
}

} // namespace graphics
} // namespace orion
