/*
 * videomode.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef VIDEOMODE_HPP_
#define VIDEOMODE_HPP_

#include <orion>
#include <config/config.hpp>

namespace orion
{

class VideoMode
{
protected:
	glm::ivec2 dimensions;
	float32 dpi;
	int32 red;
	int32 green;
	int32 blue;
	int32 alpha;
	int32 stencil;
	int32 depth;

	int32 flags;
public:
	VideoMode();
	VideoMode( const VideoMode& other );
	virtual ~VideoMode();

	int32 getAlpha() const;
	void setAlpha(int32 alpha);

	int32 getBlue() const;
	void setBlue(int32 blue);

	int32 getDepth() const;
	void setDepth(int32 depth);

	const glm::ivec2& getDimensions() const;
	void setDimensions(const glm::ivec2& dimensions);

	float32 getDpi() const;
	void setDpi(float32 dpi);

	int32 getGreen() const;
	void setGreen(int32 green);

	int32 getRed() const;
	void setRed(int32 red);

	int32 getStencil() const;
	void setStencil(int32 stencil);

	bool getFullscreen() const;
	void setFullscreen(bool val);

	bool read( Config& config , std::string path );
	bool write( Config& config , std::string path );
};

typedef std::vector<VideoMode> VideoModeSet;

} // namespace orion
#endif // VIDEOMODE_HPP_
