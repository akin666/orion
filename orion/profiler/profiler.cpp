/*
 * profiler.cpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#include "profiler.hpp"

namespace orion
{

Profiler::Profiler()
{
}

Profiler::~Profiler()
{
	clear();
}

void Profiler::clear()
{
	for( ProfilerMap::iterator iter = data.begin() ; iter != data.end() ; ++iter )
	{
		delete iter->second;
	}
	data.clear();
}

ProfilerData& Profiler::start( std::string str )
{
	ProfilerData& tmp = access( str );
	tmp.start();
	return tmp;
}

void Profiler::end( std::string str )
{
	access( str ).end();
}

ProfilerData& Profiler::access( std::string str )
{
	ProfilerMap::iterator iter = data.find( str );

	if( iter == data.end() )
	{
		ProfilerData *ptr = new ProfilerData( str );
		data[ str ] = ptr;
		return *ptr;
	}
	return *(iter->second);
}

void Profiler::print()
{
	LOG->message(" Total profiler data count %i " , data.size() );
	for( ProfilerMap::iterator iter = data.begin() ; iter != data.end() ; ++iter )
	{
		iter->second->print();
	}
}

} // namespace orion
