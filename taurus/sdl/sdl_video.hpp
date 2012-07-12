/*
 * sdl_video.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef SDL_VIDEO_HPP_
#define SDL_VIDEO_HPP_

#include "sdl_detect.hpp"
#ifdef SDL_PLATFORM
#include <video/video.hpp>
#include <stdgl>

namespace orion
{

class SDLRenderTarget;
class SDLVideo : public Video
{
protected:
	uint32 flags;

	SDLRenderTarget *rendertarget;

	void setInitialized( bool val );
	bool isInitialized();
public:
	SDLVideo();
	virtual ~SDLVideo();

	virtual void listModes( graphics::RenderTargetSettingSet& set );

	virtual bool isCursorVisible();
	virtual void setCursorVisible( bool val );

	virtual void setTitle( string8 head );
	virtual string8 getTitle();

	virtual void query();

	virtual bool apply( graphics::RenderTargetSetting& mode );
	virtual bool initialize();
	virtual void flip();
	virtual void finish();
	virtual graphics::RenderTarget& getRenderTarget();
};

} // namespace orion
#endif // SDL_PLATFORM
#endif // SDL_VIDEO_HPP_
