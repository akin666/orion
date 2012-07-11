/*
 * graphicslib.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "sdl_detect.hpp"
#ifdef SDL_PLATFORM

#include <graphics/graphicslib.hpp>
#include <stdgl>

namespace orion {

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::bindScreen()
{
	GL_TEST_START();
	glBindFramebuffer( GL_FRAMEBUFFER , GL_NULL );
	GL_TEST_END();
}

void Graphics::finish()
{
	GL_TEST_START();
	glFinish();
	GL_TEST_END();
}

} // orion

#endif // SDL_PLATFORM
