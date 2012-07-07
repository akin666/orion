/*
 * sdl_video.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "sdl_video.hpp"
#ifdef SDL_PLATFORM
#include <config/config.hpp>
#include <stdgl>
#include <graphics/graphicslib.hpp>

namespace orion {

/////
// SDLRenderTarget
/////

class SDLRenderTarget : public RenderTarget
{
protected:
	SDL_Surface* screen;
public:
	SDLRenderTarget();
	SDLRenderTarget( const VideoMode& mode );
	virtual ~SDLRenderTarget();

	bool initialize();

	virtual void bind();

	void flip();
};


SDLRenderTarget::SDLRenderTarget()
: screen( NULL )
{
}

SDLRenderTarget::SDLRenderTarget( const VideoMode& mode )
: RenderTarget( mode ),
  screen( NULL )
{
}

SDLRenderTarget::~SDLRenderTarget()
{
}

bool SDLRenderTarget::initialize()
{
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// bpp, is bitsperpixel.. well.. lets do our best.
	// TODO, there is no choice really.. 32bits.

	/*
	screen = SDL_SetVideoMode(
			mode.getDimensions().x ,
			mode.getDimensions().y ,
			32,
			SDL_OPENGL |
			( mode.getFullscreen() ? SDL_FULLSCREEN : 0x0 )
			);
	*/

	screen = SDL_SetVideoMode(
			640 ,
			480 ,
			32,
			SDL_OPENGL |
			SDL_FULLSCREEN
			);

	return screen != NULL;
}

void SDLRenderTarget::bind()
{
	Graphics::bindScreen();
}

void SDLRenderTarget::flip()
{
	SDL_GL_SwapBuffers();
}


/////
// SDLVideo
/////

#define SDLVIDEOF_NONE			0x0000
#define SDLVIDEOF_INITIALIZED	0x0001

SDLVideo::SDLVideo()
: flags(SDLVIDEOF_NONE),
  rendertarget( NULL )
{
}

SDLVideo::~SDLVideo()
{
	delete rendertarget;
	rendertarget = NULL;
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
	if( isInitialized() )
	{
		return false;
	}

	VideoMode mode;
	mode.read( *CONFIG , "video" );

//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		LOG->error("Failed to initialize SDLVideo: %s\n", SDL_GetError());
		return false;
	}

    atexit(SDL_Quit);

	if( !GL_INITIALIZATION )
	{
		LOG->error("Failed to initialize GL\n");
		return false;
	}

	rendertarget = new SDLRenderTarget( mode );

	return rendertarget->initialize();
}

void SDLVideo::flip()
{
	rendertarget->flip();
}

void SDLVideo::finish()
{
	Graphics::finish();
}

RenderTarget& SDLVideo::getRenderTarget()
{
	return *rendertarget;
}

} // namespace orion
#endif // SDL_PLATFORM
