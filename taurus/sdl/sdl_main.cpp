
// Orion SDL Platform!

#include "sdl_detect.hpp"

#ifdef SDL_PLATFORM

#include <SDL/SDL.h>

#include <profiler/profiler.hpp>
#include <application.hpp>
#include <config/jsonconfigloader.hpp>

#include <video>
#include <audio>

#include <engine>

#warning Compiling with SDL-MAIN

int main(int argc, char *argv[])
{
	orion::Engine<
		Application,
		orion::JSONConfigLoader,
		orion::Video ,
		orion::Audio ,
		orion::Log ,
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
