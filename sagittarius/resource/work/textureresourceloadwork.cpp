/*
 * textureresourceloadwork.cpp
 *
 *  Created on: 19.7.2012
 *      Author: akin
 */

#include "textureresourceloadwork.hpp"
#include <threadpool>
#include <native>

#define TEXLOADWORK_NONE		0x0000
#define TEXLOADWORK_RUNNING		0x0001

namespace orion
{

TextureResourceLoadWork::TextureResourceLoadWork()
: state( TEXLOADWORK_NONE )
{
}

TextureResourceLoadWork::~TextureResourceLoadWork()
{
}

void TextureResourceLoadWork::add( TextureResource *res )
{
	std::lock_guard<std::mutex> lock(mutex);

	loadSet.push( res );

	// Command work to load the resource.
	// If already running, no need to re-add to work que.
	// If no running, then needs to be added to work que.
	if( state == TEXLOADWORK_NONE )
	{
		queuWork( (*this) );
	}
}

bool TextureResourceLoadWork::begin()
{
	std::lock_guard<std::mutex> lock(mutex);
	state = TEXLOADWORK_RUNNING;
	return true;
}

void TextureResourceLoadWork::run()
{
	TextureResource *packet = NULL;
	while( true )
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			packet = loadSet.pop();
			if( packet == NULL  )
			{
				state = TEXLOADWORK_NONE;
				break; // Out of the loop
			}
		}

		if( !loadImageFile( packet->getPath() , packet->accessBuffer() ) )
		{
			// ERROR!
			packet->loadingError();
			continue;
		}
		packet->loadingSuccess();
	}
}

void TextureResourceLoadWork::end()
{
}

} // namespace orion 
