/*
 * video.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <orion>
#include "videomode.hpp"
#include <graphics/rendertarget.hpp>

namespace orion
{

class Video
{
protected:
	VideoMode current;
public:
	Video();
	virtual ~Video();

	const VideoMode& getMode() const;

	virtual void listModes( VideoModeSet& set );

	virtual bool isCursorVisible();
	virtual void setCursorVisible( bool val );

	virtual void setTitle( string8 head );
	virtual string8 getTitle();

	virtual bool apply( VideoMode& mode ) = 0;
	virtual bool initialize() = 0;
	virtual void flip() = 0;
	virtual void finish() = 0;
	virtual RenderTarget& getRenderTarget() = 0;
	virtual void query() = 0;
};

} // namespace orion
#endif // VIDEO_HPP_
