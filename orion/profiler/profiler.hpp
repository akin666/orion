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
	typedef std::map< string8 , ProfilerData* > ProfilerMap;

	ProfilerMap data;
public:
	Profiler();
	virtual ~Profiler();

	void clear();

	ProfilerData& start( string8 str );
	void end( string8 str );

	ProfilerData& access( string8 str );

	void print();
};

} // namespace orion

// Helpers, i think..
#define PROFILER_START( name ) createGlobal<Profiler>()->start(name)
#define PROFILER_END( name ) createGlobal<Profiler>()->end(name)

#define PROFILER_SCOPE( name ) ProfilerRAII pfraii( createGlobal<Profiler>()->access(name) )

#define PROFILER_PRINT() createGlobal<Profiler>()->print()

#endif // PROFILER_HPP_
