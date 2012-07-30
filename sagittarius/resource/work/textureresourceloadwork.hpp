/*
 * textureresourceloadwork.hpp
 *
 *  Created on: 19.7.2012
 *      Author: akin
 */

#ifndef TEXTURERESOURCELOADWORK_HPP_
#define TEXTURERESOURCELOADWORK_HPP_

#include <work>
#include <uthread>
#include <resource/textureresource.hpp>
#include <tset>

namespace orion
{

class TextureResourceLoadWork : public Work
{
protected:
	typedef TSet<TextureResource> LoadSet;
	LoadSet loadSet;

	std::mutex mutex;
	uint state;

	TextureResource *popNext();
public:
	TextureResourceLoadWork();
	virtual ~TextureResourceLoadWork();

	void add( TextureResource *res );

	virtual bool begin();
	virtual void run();
	virtual void end();
};

} // namespace orion 
#endif // TEXTURERESOURCELOADWORK_HPP_ 
