/*
 * common.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <defines.hpp>	// From the game itself.

#include "stdtypes.h"	// takes care of orion standard types.
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <glm/glm>
#include <rapidxml/rapidxml.hpp>

#define DELTA 0.0001f
#define PI 3.141593f
#define PI2 6.283185f
#define DEG2RAD 0.017453292519943
 // PI/360.0f =
#define PI_OVER_360 0.0087266462599716478846184538424431

#define US_TO_S 0.000001
#define US_TO_MS 0.001
#define S_TO_US  1000000
#define MS_TO_S 1000

#define H_IN_DAY 24
#define MIN_IN_H 60
#define S_IN_MIN 60

namespace orion {
    typedef uint32		 	UNICODE;
    typedef uint32		 	UTF32;
    typedef uint16		 	UNICODE16;
    typedef uint16		 	UTF16;
    typedef uint8		 	UTF8;
    typedef uint32		 	BufferIndex;

    // Time
    typedef int32			Year;
    typedef int32			Month;
    typedef int32			Day;
    typedef int32			Hour;
    typedef int32			Minute;
    typedef int32		 	Second;
    typedef int32 			MicroSecond;
    typedef int32 			MilliSecond;
    typedef int32		 	Tick;
    typedef int32			Timezone;

    // Time
    typedef uint64			PreciseTime;
    typedef float64			FloatTime;

    // Tick info
    const int SimulationFPS = 66;
    const float SimulationStep = 1.0f / SimulationFPS;

    typedef uint64 			EntityID;
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
