/*
 * profilerdata.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "profilerdata.hpp"
#include <platform/platform.h>

#define PROFILER_IDLE 		0
#define PROFILER_RUNNING 	1

namespace orion
{

ProfilerData::ProfilerData( )
: max( 0 ),
  min( std::numeric_limits<PreciseTime>::max() ),
  at( 0 ),
  state( PROFILER_IDLE )
{
	for( int i = 0 ; i < PROFILER_MEDIAN ; ++i )
	{
		prev[0] = 0;
	}
}

ProfilerData::ProfilerData( const ProfilerData& b )
: name( b.name ),
  max( b.max ),
  min( b.min ),
  at( b.at ),
  state( b.state )
{
	for( int i = 0 ; i < PROFILER_MEDIAN ; ++i )
	{
		prev[0] = 0;
	}
}

ProfilerData::ProfilerData( std::string name )
: name( name ),
  max( 0 ),
  min( std::numeric_limits<PreciseTime>::max() ),
  at( 0 ),
  state( PROFILER_IDLE )
{
	for( int i = 0 ; i < PROFILER_MEDIAN ; ++i )
	{
		prev[0] = 0;
	}
}

ProfilerData::~ProfilerData()
{
}

void ProfilerData::start()
{
	if( state != PROFILER_IDLE )
	{
		return;
	}

	state = PROFILER_RUNNING;
	getTime( time );
}

void ProfilerData::end()
{
	if( state == PROFILER_IDLE )
	{
		return;
	}

	PreciseTime tmp = time.us;
	getTime( time );
	tmp = time.us - tmp;

	if( tmp > max ) max = tmp;
	if( tmp < min ) min = tmp;

	prev[ at ] = tmp;
	at = (at + 1) % PROFILER_MEDIAN;

	state = PROFILER_IDLE;
}

std::string ProfilerData::getName()
{
	return name;
}

PreciseTime ProfilerData::getMax()
{
	return max;
}

PreciseTime ProfilerData::getMin()
{
	return min;
}

PreciseTime ProfilerData::getLast()
{
	return prev[(at - 1) % PROFILER_MEDIAN];
}

PreciseTime ProfilerData::getMedian()
{
	PreciseTime tmp;

	for( int i = 0 ; i < PROFILER_MEDIAN ; ++i )
	{
		tmp += prev[i];
	}

	return tmp / PROFILER_MEDIAN;
}

void ProfilerData::print()
{
	LOG->message("  - %s :\t median: %i , max: %i min: %i ." , getName().c_str() , getMedian() , getMax() , getMin() );
}

} // namespace orion
