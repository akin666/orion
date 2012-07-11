/*
 * sdl_detect.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef SDL_DETECT_HPP_
#define SDL_DETECT_HPP_

#include <orion>

#if defined( USE_SDL ) and ( defined(OS_WINDOWS) or defined(OS_LINUX) or defined(OS_MAC) )
# define SDL_PLATFORM
#endif

#endif // SDL_DETECT_HPP_
