
// Orion SDL Platform!

#include "sdl_detect.hpp"

#ifdef SDL_PLATFORM

#include <SDL/SDL.h>

#include <profiler/profiler.hpp>
#include <application.hpp>
#include <configloader.hpp>

#include <sdl/sdl_video.hpp>
#include <openal/openal_audio.hpp>

#include <engine>

#warning Compiling with SDL-MAIN

int main(int argc, char *argv[])
{
	orion::Engine<
		Application,
		orion::ConfigLoader,
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
/*
    	PROFILER_START( "keys." );
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
//                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
//                    if (event.key.keysym.sym == SDLK_ESCAPE)
//                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        PROFILER_END( "keys." );
        */
    }

    return 0;
}

#endif // SDL_PLATFORM
