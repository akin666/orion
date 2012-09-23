/*
 * Tween.hpp
 *
 *  Created on: 23.9.2012
 *      Author: akin
 */

#ifndef TWEEN_HPP_
#define TWEEN_HPP_

#include <glm/glm.hpp>

namespace tween
{

class Linear
{
public:
	template <class CType> void update( CType& value , CType total , double position , double delta )
	{
		double tt = position + delta;
		double tpos = glm::max( tt , 1.0 );
		delta = 0; // TODO .. what happens if position + delta > 1.0 !!!1

		// add to value, delta amount, from last,
		value += total * delta;
	}
};

class EaseIn
{
public:
	template <class CType> void update( CType& value , CType total , double position , double delta )
	{

	}
};

} // namespace tween
#endif // TWEEN_HPP_
