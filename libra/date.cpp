/*
 * Date.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "date"
#include <native>

namespace orion {

Date::Date()
: year( 0 ),
  month( 0 ),
  day( 0 ),
  hour( 0 ),
  minute( 0 ),
  second( 0 ),
  weekday( 0 ),
  dayOfYear( 0 ),
  timezone( 0 )
{
}

Date::Date(const Date & other)
: year( other.year ),
  month( other.month ),
  day( other.day ),
  hour( other.hour ),
  minute( other.minute ),
  second( other.second ),
  weekday( other.weekday ),
  dayOfYear( other.dayOfYear ),
  timezone( other.timezone )
{
}

Day Date::getWeekday() const
{
	return weekday;
}

void Date::setWeekday(Day weekday)
{
	this->weekday = weekday;
}

Day Date::getDay() const
{
	return day;
}

void Date::setDay(Day day)
{
	this->day = day;
}

Day Date::getDayOfYear() const
{
	return dayOfYear;
}

void Date::setDayOfYear(Day dayOfYear)
{
	this->dayOfYear = dayOfYear;
}

Hour Date::getHour() const
{
	return hour;
}

void Date::setHour(Hour hour)
{
	this->hour = hour;
}

Minute Date::getMinute() const
{
	return minute;
}

void Date::setMinute(Minute minute)
{
	this->minute = minute;
}

Month Date::getMonth() const
{
	return month;
}

void Date::setMonth(Month month)
{
	this->month = month;
}

Second Date::getSecond() const
{
	return second;
}

void Date::setSecond(Second second)
{
	this->second = second;
}

Timezone Date::getTimezone() const
{
	return timezone;
}

void Date::setTimezone(Timezone timezone)
{
	this->timezone = timezone;
}

Year Date::getYear() const
{
	return year;
}

void Date::setYear(Year year)
{
	this->year = year;
}

void Date::parse( string8 string )
{
}

void Date::update()
{
	getTime( *this );
}

string8 Date::toString()
{
	return "";
}

} // namespace orion
