/*
 * common.cpp
 *
 *  Created on: 16.7.2012
 *      Author: akin
 */

#include "common.hpp"

namespace orion {

uint8 getByteSize( ColorMode mode )
{
	switch( mode )
	{
		case RGB8 		: return 3;
		case RGBA8 		: return 4;
		case ARGB8 		: return 4;
		case ALPHA8 	: return 1;
		case LUMINANCE 	: return 1;
		case INTENSITY 	: return 1;
		case RGBA12 	: return 6;
		case RGBA16 	: return 8;
		case RGBA32 	: return 16;
		case RGBA32F 	: return 16;
		case DEPTH8 	: return 1;
		case DEPTH16 	: return 2;
		case DEPTH24 	: return 3;
		case DEPTH32 	: return 4;
		default			: return 0;
	}
	return 0;
}

uint8 getNumberOfElements( ColorMode mode )
{
	switch( mode )
	{
		case RGB8 		: return 3;
		case RGBA8 		: return 4;
		case ARGB8 		: return 4;
		case ALPHA8		: return 1;
		case LUMINANCE 	: return 1;
		case INTENSITY 	: return 1;
		case RGBA12 	: return 4;
		case RGBA16 	: return 4;
		case RGBA32 	: return 4;
		case RGBA32F 	: return 4;
		case DEPTH8 	: return 1;
		case DEPTH16 	: return 1;
		case DEPTH24 	: return 1;
		case DEPTH32 	: return 1;
		default			: return 0;
	}
	return 0;
}

} // namespace orion

