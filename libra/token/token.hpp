/*
 * token.hpp
 *
 *  Created on: 22.6.2012
 *      Author: akin
 */

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <orion>

namespace orion
{

class Token
{
public:
	typedef uint TokenID;
public:
	Token();
	virtual ~Token();

	TokenID id;
};

}

#endif // TOKEN_HPP_
