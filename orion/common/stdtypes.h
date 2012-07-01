/*
 * stdtypes.h
 *
 *  Created on: 1.7.2012
 *      Author: akin
 *
 *      defines orion specific standard types.
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_

#include <limits>	// c++ limits
#include <climits>	// int limits
#include <cfloat>	// float limits
#include <cstdint>	// int8_t, int16_t, int32_t,int64_t , uint8_t, uint16_t, uint32_t, uint64_t etc.

#ifndef SKIP_STANDARD_TYPES
	// signed types
	typedef int8_t 		int8;
	typedef int16_t		int16;
	typedef int32_t		int32;
	typedef int64_t 	int64;

	// unsigned types
	typedef uint8_t		uint8;
	typedef uint16_t	uint16;
	typedef uint32_t	uint32;
	typedef uint64_t 	uint64;

	// floating point
	typedef float		float32;
	typedef double		float64;
//	typedef quad		float128;
#endif

#ifndef SKIP_HELPER_TYPES
	typedef int8		 	schar;
	typedef uint8		 	uchar;
	typedef int16		 	sshort;
	typedef uint16		 	ushort;
	typedef int32 			sint;
	typedef uint32		 	uint;
	typedef int64 			slong;
	typedef uint64		 	ulong;
    typedef float32			vec;
#endif

#endif // STDTYPES_H_
