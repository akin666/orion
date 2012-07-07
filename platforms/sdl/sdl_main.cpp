
// Orion SDL Platform!

#include "sdl_detect.hpp"

#ifdef SDL_PLATFORM

#include <SDL/SDL.h>

#include <profiler/profiler.hpp>
#include <application.hpp>
#include <config/jsonconfigloader.hpp>

#include <sdl/sdl_video.hpp>
#include <openal/openal_audio.hpp>

#include <engine>

#warning Compiling with SDL-MAIN

int main(int argc, char *argv[])
{
	orion::Engine<
		Application,
		orion::JSONConfigLoader,
		orion::SDLVideo ,
		orion::OpenALAudio ,
		orion::Log ,
		orion::ResourceManager ,
		orion::Allocator
		>
		app;

   if( !app.initialize( argc , argv ) )
   {
	   return 1;
   }

    // program main loop
    while( app.stillRunning() )
    {
    	app.run();
    }

    return 0;
}

#endif // SDL_PLATFORM
