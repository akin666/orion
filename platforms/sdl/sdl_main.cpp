
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

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

   if( !app.initialize( argc , argv ) )
   {
	   return 1;
   }

    // program main loop
    while( app.stillRunning() )
    {
    	app.run();

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
        
        // clear screen
    	PROFILER_START( "fillscreen." );
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        PROFILER_END( "fillscreen." );

        // DRAWING ENDS HERE

        PROFILER_PRINT();
        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

#endif // SDL_PLATFORM
