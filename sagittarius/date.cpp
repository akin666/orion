/*
 * Date.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "date"
#include <native>

namespace orion {

void add( Time& s , const Time& s2 )
{
	s.us += s2.us;
}

void subtract( Time& s , const Time& s2 )
{
	s.us -= s2.us;
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

Date::Date(string8 str)
{
	(*this) = ::orion::parseTime( str );
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
	return (us == val.us);
}

bool Date::operator !=(const Date & val) const
{
	return !(operator == ( val ));
}

bool Date::operator <(const Date & val) const
{
	return us < val.us;
}

bool Date::operator >(const Date & val) const
{
	return us > val.us;
}

bool Date::operator <=(const Date & val) const
{
	return us <= val.us;
}

bool Date::operator >=(const Date & val) const
{
	return us >= val.us;
}

Date & Date::operator =(const Date & val)
{
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

void Date::parse(string8 string)
{
	(*this) = ::orion::parseTime( string );
}

void Date::update()
{
	::orion::getTime( *this );
}

string8 Date::toString()
{
	return ::orion::timeToString( *this );
}

} // namespace orion
