
// Orion SDL Platform!

#include "sdl_detect.hpp"

#ifdef SDL_PLATFORM

#include <stdgl>

#include <profiler/profiler.hpp>
#include <application.hpp>
#include <sdl/sdl_video.hpp>
#include <openal/openal_audio.hpp>
#include <configloader.hpp>

#include <main>

using namespace orion;

int main ( int argc, char** argv )
{
	Main<
		Application,
		ConfigLoader,
		SDLVideo ,
		OpenALAudio ,
		Log ,
		ResourceManager ,
		Allocator
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
