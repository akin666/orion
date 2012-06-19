/*
 * common.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <defines.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <glm/glm>
#include <rapidxml/rapidxml.hpp>

#define DELTA 0.0001f
#define PI 3.141593f
#define PI2 6.283185f
#define DEG2RAD 0.017453292519943
 // PI/360.0f =
#define PI_OVER_360 0.0087266462599716478846184538424431

#define US_TO_S 1000000
#define MS_TO_S 1000

#define H_IN_DAY 24
#define MIN_IN_H 60
#define S_IN_MIN 60

namespace orion {

	typedef signed int 		sint;
	typedef unsigned int 	uint;
	typedef signed char 	schar;
	typedef unsigned char 	uchar;
	typedef signed short 	sshort;
	typedef unsigned short 	ushort;
    typedef float 			vec;

    typedef unsigned int 	UNICODE;
    typedef unsigned int 	UTF32;
    typedef unsigned short 	UNICODE16;
    typedef unsigned short 	UTF16;
    typedef unsigned char 	UTF8;
    typedef unsigned int 	BufferIndex;

    // Time
    typedef int				Year;
    typedef int				Month;
    typedef int				Day;
    typedef int				Hour;
    typedef int				Minute;
    typedef unsigned int 	Second;
    typedef unsigned int 	MicroSecond;
    typedef unsigned int 	MilliSecond;
    typedef unsigned int 	Tick;
    typedef int				Timezone;

    // Tick info
    const int SimulationFPS = 66;
    const float SimulationStep = 1.0f / SimulationFPS;

    typedef uint 			EntityID;
    typedef std::vector<EntityID> EntitySet;
    typedef std::map<std::string, EntityID> EntityNameMap;
    typedef std::map<std::string, EntitySet> EntitySetMap;

	enum ColorMode
	{
		RGB = 1,
		RGBA = 2,
		ARGB = 3,
		ALPHA = 4,
		LUMINANCE = 5,
		INTENSITY = 6,
		RGBA12 = 7,
		RGBA16 = 8,
		RGBA32 = 9
	};
} // orion

#endif // COMMON_HPP_
