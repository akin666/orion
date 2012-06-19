/*
 * Date.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "date.hpp"
#include <platform/platform.h>

namespace orion {

void add( Time& s , const Time& s2 )
{
	MicroSecond overall = s.us + s2.us;
	s.us = overall % US_TO_S;

	if( s.us < 0 )
	{
		--s.s; // take one
		s.us += US_TO_S; // add one
	}

	s.s += s2.s + ( overall / US_TO_S );
}

void subtract( Time& s , const Time& s2 )
{
	MicroSecond overall = s.us + (-s2.us);
	s.us = overall % US_TO_S;

	if( s.us < 0 )
	{
		--s.s; // take one
		s.us += US_TO_S; // add one
	}

	s.s += (-s2.s) + ( overall / US_TO_S );
}

Date::Date()
{
}

Date::Date(const Date & other)
{
}

Date::Date(const Time & other)
{
}

Date::Date(Year year, Month month, Day day, Hour hour, Minute minute, Second second, MicroSecond ms)
{
}

Date::Date(std::string string)
{
	(*this) = ::orion::parseTime( string );
}

Date::~Date()
{
}

bool Date::after(const Date & val)
{
	return (*this) > val;
}

bool Date::before(const Date & val)
{
	return (*this) < val;
}

bool Date::operator ==(const Date & val) const
{
	return (s == val.s) && (us == val.us);
}

bool Date::operator !=(const Date & val) const
{
	return !(operator == ( val ));
}

bool Date::operator <(const Date & val) const
{
	if( s == val.s )
	{
		return us < val.us;
	}
	return s < val.s;
}

bool Date::operator >(const Date & val) const
{
	if( s == val.s )
	{
		return us > val.us;
	}
	return s > val.s;
}

bool Date::operator <=(const Date & val) const
{
	if( s == val.s )
	{
		return us <= val.us;
	}
	return s < val.s;
}

bool Date::operator >=(const Date & val) const
{
	if( s == val.s )
	{
		return us >= val.us;
	}
	return s > val.s;
}

Date & Date::operator =(const Date & val)
{
	s = val.s;
	us = val.us;

	return *this;
}

Date & Date::operator +=(const Date & val)
{
	add( *this , val );
	return *this;
}

Date & Date::operator -=(const Date & val)
{
	subtract( *this , val );
	return *this;
}

Date Date::operator -(const Date & val) const
{
	Date tmp( *this );
	subtract( tmp , val );
	return tmp;
}

Date Date::operator +(const Date & val) const
{
	Date tmp( *this );
	add( tmp , val );
	return tmp;
}

Year Date::getYear()
{
	return ::orion::getYear( *this );
}

Day Date::getDayOfYear()
{
	return ::orion::getDayOfYear( *this );
}

Day Date::getDayOfMonth()
{
	return ::orion::getDayOfMonth( *this );
}

Hour Date::getHour()
{
	return ::orion::getHour( *this );
}

Minute Date::getMinute()
{
	return ::orion::getMinute( *this );
}

Month Date::getMonth()
{
	return ::orion::getMonth( *this );
}

Second Date::getSecond()
{
	return ::orion::getSecond( *this );
}

MilliSecond Date::getMilliSecond()
{
	return ::orion::getMilliSecond( *this );
}

MicroSecond Date::getMicroSecond()
{
	return ::orion::getMicroSecond( *this );
}

Time& Date::getTime()
{
	return *this;
}

Timezone Date::getTimezoneOffset()
{
	return ::orion::getTimezone();
}

void Date::parse(std::string string)
{
	(*this) = ::orion::parseTime( string );
}

void Date::update()
{
	::orion::getTime( *this );
}

std::string Date::toString()
{
	return ::orion::timeToString( *this );
}

} // namespace orion
