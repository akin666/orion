/*
 * Date.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef DATE_HPP_
#define DATE_HPP_

#include <orion>

namespace orion {

class Date : public Time
{
public:
	Date();
	Date( const Time& other );
	Date( const Date& other );
	Date( Year year = 0 , Month month = 0 , Day day = 0 , Hour hour = 0 , Minute minute = 0 , Second second = 0 , MicroSecond ms = 0 );
	Date( std::string string );
	virtual ~Date();

	bool after( const Date& val );
	bool before( const Date& val );

	bool operator == ( const Date& val ) const;
	bool operator != ( const Date& val ) const;
	bool operator < ( const Date& val ) const;
	bool operator > ( const Date& val ) const;
	bool operator <= ( const Date& val ) const;
	bool operator >= ( const Date& val ) const;

	Date& operator = ( const Date& val );
	Date& operator += ( const Date& val );
	Date& operator -= ( const Date& val );
	Date operator - ( const Date& val ) const;
	Date operator + ( const Date& val ) const;

	Year getYear();
	Day getDayOfYear();
	Day getDayOfMonth();
	Hour getHour();
	Minute getMinute();
	Month getMonth();
	Second getSecond();
	MilliSecond getMilliSecond();
	MicroSecond getMicroSecond();

	Time& getTime();

	Timezone getTimezoneOffset();

	void parse( std::string string );

	void update();

	std::string toString();
};

} // namespace orion
#endif // TIME_HPP_
