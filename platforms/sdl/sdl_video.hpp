/*
 * sdl_video.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef SDL_VIDEO_HPP_
#define SDL_VIDEO_HPP_

#include <video/video.hpp>

namespace orion
{

class SDLVideo : public Video
{
protected:
	uint32 flags;

	void setInitialized( bool val );
	bool isInitialized();
public:
	SDLVideo();
	virtual ~SDLVideo();

	virtual void listModes( VideoModeSet& set );

	virtual bool isCursorVisible();
	virtual void setCursorVisible( bool val );

	virtual void setTitle( std::string head );
	virtual std::string getTitle();

	virtual bool apply( VideoMode& mode );
	virtual bool initialize();
	virtual void flip();
	virtual void finish();
	virtual RenderTarget& getRenderTarget();
};

} // namespace orion
#endif // SDL_VIDEO_HPP_
