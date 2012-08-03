/*
 * duration.hpp
 *
 *  Created on: 26.7.2012
 *      Author: akin
 */

#ifndef DURATION_HPP_
#define DURATION_HPP_

#include <orion>

namespace orion
{

class Duration
{
protected:
	PreciseTime begin;
	PreciseTime length;
	string8 name;
public:
	Duration();

	void setName( const string8& name );
	string8 getName() const;

	void setBegin( PreciseTime begin );
	PreciseTime getBegin() const;

	void setLength( PreciseTime length );
	PreciseTime getLength() const;

	PreciseTime getEnd() const;

	void setup( PreciseTime begin , PreciseTime length , const string8& name );
};

} // namespace orion 
#endif // DURATION_HPP_ 
