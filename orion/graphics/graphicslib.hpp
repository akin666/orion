/*
 * graphicslib.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSLIB_HPP_
#define GRAPHICSLIB_HPP_

namespace orion {

class Graphics
{
private:
	Graphics();
	~Graphics();
public:
	static void bindScreen();
	static void finish();
};

} // orion

#endif // GRAPHICSLIB_HPP_
