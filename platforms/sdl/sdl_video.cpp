/*
 * sdl_video.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "sdl_video.hpp"
#include <config/config.hpp>

namespace orion
{

#define SDLVIDEOF_NONE			0x0000
#define SDLVIDEOF_INITIALIZED	0x0001

SDLVideo::SDLVideo()
: flags(SDLVIDEOF_NONE)
{
}

SDLVideo::~SDLVideo()
{
}

void SDLVideo::setInitialized( bool val )
{
	if( val )
	{
		flags |= SDLVIDEOF_INITIALIZED;
	}
	else
	{
		flags &= ~SDLVIDEOF_INITIALIZED;
	}
}

bool SDLVideo::isInitialized()
{
	return (flags & SDLVIDEOF_INITIALIZED) != 0;
}

void SDLVideo::listModes(VideoModeSet& set)
{
}

bool SDLVideo::isCursorVisible()
{
	return true;
}

void SDLVideo::setCursorVisible(bool val)
{
}

void SDLVideo::setTitle(std::string head)
{
}

std::string SDLVideo::getTitle()
{
	return "";
}

bool SDLVideo::apply(VideoMode& mode)
{
	if( isInitialized() )
	{
		return false;
	}

	return mode.write( *CONFIG , "video" );
}

bool SDLVideo::initialize()
{
	VideoMode mode;

	mode.read( *CONFIG , "video" );

	return true;
}

void SDLVideo::flip()
{
}

void SDLVideo::finish()
{
}
RenderTarget tt;
RenderTarget& SDLVideo::getRenderTarget()
{
	return tt;
}

} // namespace orion
