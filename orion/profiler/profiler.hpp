/*
 * profiler.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#ifndef PROFILER_HPP_
#define PROFILER_HPP_

#include <orion>
#include "profilerdata.hpp"

namespace orion
{

class Profiler
{
protected:
	typedef std::map< std::string , ProfilerData* > ProfilerMap;

	ProfilerMap data;
public:
	Profiler();
	virtual ~Profiler();

	void clear();

	ProfilerData& start( std::string str );
	void end( std::string str );

	ProfilerData& access( std::string str );

	void print();
};

} // namespace orion

// Helpers, i think..
#define PROFILER_START( name ) createGlobal<Profiler>()->start(name)
#define PROFILER_END( name ) createGlobal<Profiler>()->end(name)

#define PROFILER_SCOPE( name ) ProfilerRAII pfraii( createGlobal<Profiler>()->access(name) )

#define PROFILER_PRINT() createGlobal<Profiler>()->print()

#endif // PROFILER_HPP_
