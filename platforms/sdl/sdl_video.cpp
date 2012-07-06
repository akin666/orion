/*
 * sdl_video.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "sdl_video.hpp"

namespace orion
{

SDLVideo::SDLVideo()
{
}

SDLVideo::~SDLVideo()
{
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
	return true;
}

bool SDLVideo::initialize()
{
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
