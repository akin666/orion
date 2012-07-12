/*
 * rendertargetsetting.hpp
 *
 *  Created on: 12.7.2012
 *      Author: akin
 */

#ifndef RENDERTARGETSETTING_HPP_
#define RENDERTARGETSETTING_HPP_

#include <orion>
#include <config/config.hpp>

namespace orion {
namespace graphics {

class RenderTargetSetting
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
	RenderTargetSetting();
	RenderTargetSetting( const RenderTargetSetting& other );
	virtual ~RenderTargetSetting();

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

	bool read( Config& config , string8 path );
	bool write( Config& config , string8 path );
};

typedef std::vector<RenderTargetSetting> RenderTargetSettingSet;

} // namespace graphics 
} // namespace orion 
#endif // RENDERTARGETSETTING_HPP_ 
