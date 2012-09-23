/*
 * Tweener.hpp
 *
 *  Created on: 23.9.2012
 *      Author: akin
 */

#ifndef TWEENER_HPP_
#define TWEENER_HPP_

namespace tween
{

template <class CType , class TweenType>
class Tweener
{
protected:
	CType& value;
	CType total;
	double last;
	double begin;
	double length;
public:
	Tweener( CType& value , CType total , double begin , double end )
	: value( value ) // what thing to modify?
	, total( total ) // how much to add
	, last( begin )  // the position we got last time
	, begin( begin ) // the position where it all began
	, length( end - begin ) // total length of the thing
	{
	}

	void update( double at )
	{
		// normalize all
		double delta = (at - last) / length;
		double position = (last - begin) / length;

		TweenType::update<CType>( value , total , position , delta );
		last = at;
	}

	bool finished()
	{
		return last >= (begin+length);
	}
};

} // namespace tween
#endif // TWEENER_HPP_
