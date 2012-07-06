/*
 * videomode.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "videomode.hpp"

namespace orion
{

#define VIDMODEF_NONE			0x0000
#define VIDMODEF_FULLSCREEN		0x0001

VideoMode::VideoMode()
: 	dpi(0),
	red(0),
	green(0),
	blue(0),
	alpha(0),
	stencil(0),
	depth(0),
	flags(VIDMODEF_NONE)
{
}

VideoMode::VideoMode( const VideoMode& other )
: 	dpi(other.dpi),
	red(other.red),
	green(other.green),
	blue(other.blue),
	alpha(other.alpha),
	stencil(other.stencil),
	depth(other.depth),
	flags(other.flags)
{
}

VideoMode::~VideoMode()
{
}

int32 VideoMode::getAlpha() const
{
	return alpha;
}

void VideoMode::setAlpha(int32 alpha)
{
	this->alpha = alpha;
}

int32 VideoMode::getBlue() const
{
	return blue;
}

void VideoMode::setBlue(int32 blue)
{
	this->blue = blue;
}

int32 VideoMode::getDepth() const
{
	return depth;
}

void VideoMode::setDepth(int32 depth)
{
	this->depth = depth;
}

const glm::ivec2& VideoMode::getDimensions() const
{
	return dimensions;
}

void VideoMode::setDimensions(const glm::ivec2& dimensions)
{
	this->dimensions = dimensions;
}

float32 VideoMode::getDpi() const
{
	return dpi;
}

void VideoMode::setDpi(float32 dpi)
{
	this->dpi = dpi;
}

int32 VideoMode::getGreen() const
{
	return green;
}

void VideoMode::setGreen(int32 green)
{
	this->green = green;
}

int32 VideoMode::getRed() const
{
	return red;
}

void VideoMode::setRed(int32 red)
{
	this->red = red;
}

int32 VideoMode::getStencil() const
{
	return stencil;
}

void VideoMode::setStencil(int32 stencil)
{
	this->stencil = stencil;
}

bool VideoMode::getFullscreen() const
{
	return (flags&VIDMODEF_FULLSCREEN) != 0;
}

void VideoMode::setFullscreen(bool val)
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

bool VideoMode::read( Config& config , std::string path )
{
	glm::ivec2 dim;
	dim.x = config.get<int32>(	path + ".width" );
	dim.y = config.get<int32>(	path + ".height" );
	setDimensions( dim );

	setDpi( config.get<float32>(	path + ".dpi" ) );
	setRed( config.get<int32>(		path + ".red" ) );
	setGreen( config.get<int32>(	path + ".green" ) );
	setBlue( config.get<int32>(		path + ".blue" ) );
	setAlpha( config.get<int32>(	path + ".alpha" ) );
	setStencil( config.get<int32>(	path + ".stencil" ) );
	setDepth( config.get<int32>(	path + ".depth" ) );
	setFullscreen( config.get<bool>(path + ".fullscreen" ) );

	return true;
}

bool VideoMode::write( Config& config , std::string path )
{
	config.set<int32>(		path + ".width", 		getDimensions().x );
	config.set<int32>(		path + ".height",		getDimensions().y );
	config.set<float32>(	path + ".dpi", 			getDpi() );
	config.set<int32>(		path + ".red", 			getRed() );
	config.set<int32>(		path + ".green", 		getGreen() );
	config.set<int32>(		path + ".blue", 		getBlue() );
	config.set<int32>(		path + ".alpha", 		getAlpha() );
	config.set<int32>(		path + ".stencil", 		getStencil() );
	config.set<int32>(		path + ".depth", 		getDepth() );
	config.set<bool>(		path + ".fullscreen", 	getFullscreen() );

	return true;
}

} // namespace orion
