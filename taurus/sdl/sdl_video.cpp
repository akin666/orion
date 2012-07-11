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

#include <orionevent>

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
	/*
    SDL_GL_RED_SIZE,
    SDL_GL_GREEN_SIZE,
    SDL_GL_BLUE_SIZE,
    SDL_GL_ALPHA_SIZE,
    SDL_GL_BUFFER_SIZE,
    SDL_GL_DOUBLEBUFFER,
    SDL_GL_DEPTH_SIZE,
    SDL_GL_STENCIL_SIZE,
    SDL_GL_ACCUM_RED_SIZE,
    SDL_GL_ACCUM_GREEN_SIZE,
    SDL_GL_ACCUM_BLUE_SIZE,
    SDL_GL_ACCUM_ALPHA_SIZE,
    SDL_GL_STEREO,
    SDL_GL_MULTISAMPLEBUFFERS,
    SDL_GL_MULTISAMPLESAMPLES,
    SDL_GL_ACCELERATED_VISUAL,
    SDL_GL_SWAP_CONTROL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    */

	screen = SDL_SetVideoMode(
			640 ,
			480 ,
			32,
			SDL_OPENGL |
			0x0
			//SDL_FULLSCREEN
			);

	if( !GL_INITIALIZATION )
	{
		LOG->error("Failed to initialize GL\n");
		return false;
	}

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
	return SDL_ShowCursor( -1 ) == 1;
}

void SDLVideo::setCursorVisible(bool val)
{
	SDL_ShowCursor( val ? 1 : 0 );
}

void SDLVideo::setTitle(string8 head)
{
}

string8 SDLVideo::getTitle()
{
	return "";
}

void SDLVideo::query()
{
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        // check for messages
        switch( event.type )
        {
			case SDL_QUIT:
			{
				ApplicationEvent orionEvent( ApplicationEvent::Quit );
				sendEvent<ApplicationEvent>( orionEvent );
				break;
			}
			case SDL_VIDEORESIZE :
			{
				ApplicationEvent orionEvent( ApplicationEvent::Resized );
				sendEvent<ApplicationEvent>( orionEvent );
				break;
			}
			case SDL_MOUSEMOTION:
			{
				MotionEvent orionEvent(
						glm::vec2(event.motion.xrel , event.motion.yrel),
						glm::vec2(event.motion.x , event.motion.y),
						event.motion.which
						);
				sendEvent<MotionEvent>( orionEvent );
				break;
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
			{
				KeyEvent orionEvent(
						(event.button.state == SDL_KEYDOWN ? KeyEvent::Down : KeyEvent::Up) ,
						KeyEvent::Mouse,
						0,
						event.button.button,
						glm::vec2(event.button.x , event.button.y),
						event.button.which
						);
				sendEvent<KeyEvent>( orionEvent );
				break;
			}
			case SDL_KEYUP:
			case SDL_KEYDOWN:
			{
				KeyEvent orionEvent(
						(event.key.state == SDL_KEYDOWN ? KeyEvent::Down : KeyEvent::Up) ,
						KeyEvent::Keyboard,
						event.key.keysym.unicode,
						event.key.keysym.sym,
						event.key.which
						);
				sendEvent<KeyEvent>( orionEvent );
				break;
			}
			default:
			{
				break;
			}
        }
    }
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

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		LOG->error("Failed to initialize SDLVideo: %s\n", SDL_GetError());
		return false;
	}

    atexit(SDL_Quit);

    // Configure default things:
    SDL_EnableUNICODE( 1 ); // translate key inputs into unicode.

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
