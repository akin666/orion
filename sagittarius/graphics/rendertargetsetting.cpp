/*
 * rendertargetsetting.cpp
 *
 *  Created on: 12.7.2012
 *      Author: akin
 */

#include "rendertargetsetting.hpp"

namespace orion
{
namespace graphics
{

#define VIDMODEF_NONE                   0x0000
#define VIDMODEF_FULLSCREEN             0x0001

RenderTargetSetting::RenderTargetSetting()
:   dpi(0),
	red(0),
	green(0),
	blue(0),
	alpha(0),
	stencil(0),
	depth(0),
	flags(VIDMODEF_NONE)
{
}

RenderTargetSetting::RenderTargetSetting( const RenderTargetSetting& other )
:   dpi(other.dpi),
	red(other.red),
	green(other.green),
	blue(other.blue),
	alpha(other.alpha),
	stencil(other.stencil),
	depth(other.depth),
	flags(other.flags)
{
}

RenderTargetSetting::~RenderTargetSetting()
{
}

int32 RenderTargetSetting::getAlpha() const
{
	return alpha;
}

void RenderTargetSetting::setAlpha(int32 alpha)
{
	this->alpha = alpha;
}

int32 RenderTargetSetting::getBlue() const
{
	return blue;
}

void RenderTargetSetting::setBlue(int32 blue)
{
	this->blue = blue;
}

int32 RenderTargetSetting::getDepth() const
{
	return depth;
}

void RenderTargetSetting::setDepth(int32 depth)
{
	this->depth = depth;
}

const glm::ivec2& RenderTargetSetting::getDimensions() const
{
	return dimensions;
}

void RenderTargetSetting::setDimensions(const glm::ivec2& dimensions)
{
	this->dimensions = dimensions;
}

float32 RenderTargetSetting::getDpi() const
{
	return dpi;
}

void RenderTargetSetting::setDpi(float32 dpi)
{
	this->dpi = dpi;
}

int32 RenderTargetSetting::getGreen() const
{
	return green;
}

void RenderTargetSetting::setGreen(int32 green)
{
	this->green = green;
}

int32 RenderTargetSetting::getRed() const
{
	return red;
}

void RenderTargetSetting::setRed(int32 red)
{
	this->red = red;
}

int32 RenderTargetSetting::getStencil() const
{
	return stencil;
}

void RenderTargetSetting::setStencil(int32 stencil)
{
	this->stencil = stencil;
}

bool RenderTargetSetting::getFullscreen() const
{
	return (flags&VIDMODEF_FULLSCREEN) != 0;
}

void RenderTargetSetting::setFullscreen(bool val)
{
	if( val )
	{
		flags |= VIDMODEF_FULLSCREEN;
	}
	else
	{
		flags &= ~VIDMODEF_FULLSCREEN;
	}
}

bool RenderTargetSetting::read( Config& config , string8 path )
{
	glm::ivec2 dim;
	dim.x = config.get<int32>(      path + ".width" , 640 );
	dim.y = config.get<int32>(      path + ".height" , 480 );
	setDimensions( dim );

	setDpi( config.get<float32>(    path + ".dpi" , 96 ) );
	setRed( config.get<int32>(      path + ".red" , 8 ) );
	setGreen( config.get<int32>(    path + ".green" , 8 ) );
	setBlue( config.get<int32>(     path + ".blue" , 8 ) );
	setAlpha( config.get<int32>(    path + ".alpha" , 8 ) );
	setStencil( config.get<int32>(  path + ".stencil" , 0 ) );
	setDepth( config.get<int32>(    path + ".depth" , 32 ) );
	setFullscreen( config.get<bool>(path + ".fullscreen" , false ) );

	return true;
}

bool RenderTargetSetting::write( Config& config , string8 path )
{
	config.set<int32>(              path + ".width",        getDimensions().x );
	config.set<int32>(              path + ".height",       getDimensions().y );
	config.set<float32>(    path + ".dpi",                  getDpi() );
	config.set<int32>(              path + ".red",          getRed() );
	config.set<int32>(              path + ".green",        getGreen() );
	config.set<int32>(              path + ".blue",         getBlue() );
	config.set<int32>(              path + ".alpha",        getAlpha() );
	config.set<int32>(              path + ".stencil",      getStencil() );
	config.set<int32>(              path + ".depth",        getDepth() );
	config.set<bool>(               path + ".fullscreen",   getFullscreen() );

	return true;
}

} // namespace graphics 
} // namespace orion 
