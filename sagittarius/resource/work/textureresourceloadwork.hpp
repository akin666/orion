/*
 * textureresourceloadwork.hpp
 *
 *  Created on: 19.7.2012
 *      Author: akin
 */

#ifndef TEXTURERESOURCELOADWORK_HPP_
#define TEXTURERESOURCELOADWORK_HPP_

#include <work>

namespace orion
{

class TextureResourceLoadWork : public Work
{
public:
	TextureResourceLoadWork();
	virtual ~TextureResourceLoadWork();

	virtual bool begin();
	virtual void run();
	virtual void end();
};

} // namespace orion 
#endif // TEXTURERESOURCELOADWORK_HPP_ 
