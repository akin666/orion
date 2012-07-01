/*
 * profilerdata.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#ifndef PROFILERDATA_HPP_
#define PROFILERDATA_HPP_

#include <orion>
#define PROFILER_MEDIAN 10

namespace orion
{

class ProfilerData
{
protected:
	std::string name;

	PreciseTime max;
	PreciseTime min;
	PreciseTime prev[PROFILER_MEDIAN];

	Time time;

	int32 at;

	int32 state;
public:
	ProfilerData( );
	ProfilerData( const ProfilerData& b );
	ProfilerData( std::string name );
	virtual ~ProfilerData();

	void start();
	void end();

	std::string getName();
	PreciseTime getMax();
	PreciseTime getMin();
	PreciseTime getLast();
	PreciseTime getMedian();

	void print();
};

class ProfilerRAII
{
protected:
	ProfilerData& data;
public:
	ProfilerRAII( ProfilerData& data )
	: data( data )
	{
		data.start();
	}

	~ProfilerRAII()
	{
		data.end();
	}
};

} // namespace orion
#endif // PROFILERDATA_HPP_
