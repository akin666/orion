/*
 * common.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <defines.hpp>	// From the game itself.

#include <os>			// Operating system
#include <stdtypes>		// takes care of orion standard types.
#include <colortypes>	// takes care of orion standard types.
#include <iostream>		// C++ base
#include <vector>		// Vector container
#include <map>			// Map container
#include <list>			// List container
#include <string>		// string8, string32
#include <glm/glm>		// Math libraries
#include <stdexcept>	// Exceptions
#include <atomic>		// atomic things.
#include <random>
#include <time>

namespace orion {
	//typedef std::basic_string<UTF8> 	string8; // this just doesnt work, the std::string conversions & candy is too deeply integrated into c++.
	typedef std::basic_string<UNICODE> string32;

    // Tick info
    const int SimulationFPS = 66;
    const float SimulationStep = 1.0f / SimulationFPS;

    typedef uint64 EntityID;
    typedef std::vector<EntityID> EntitySet;
    typedef std::map<string8, EntityID> EntityNameMap;
    typedef std::map<string8, EntitySet> EntitySetMap;

    typedef std::vector<string8> StringSet;

	typedef string8::size_type StringPos;

	typedef string8			ResourceID;

	enum ShaderType {
		ShaderUnknown = 0,   // 0.0
		ShaderFragment = 1,  // 2.0
		ShaderVertex = 2,    // 2.0
		ShaderGeometry = 3,  // 3.2
		ShaderControl = 4,   // 4.0
		ShaderEvaluation = 5 // 4.0
	};

	// UNICODE <==> UTF8 String conversion operations:
	// THROWS EXCEPTIONS!
	void convertText( string8& input, string32& add );
	void convertText( string32& input, string8& add );

	void initCommon();
} // orion

#endif // COMMON_HPP_
