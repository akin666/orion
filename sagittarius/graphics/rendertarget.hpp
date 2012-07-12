/*
 * rendertarget.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include "rendertargetsetting.hpp"

namespace orion {
namespace graphics {

class RenderTarget
{
protected:
	RenderTargetSetting mode;
public:
	RenderTarget();
	RenderTarget( const RenderTargetSetting& mode );
	virtual ~RenderTarget();

	RenderTargetSetting& getVideoMode();

	virtual void bind();
};

} // namespace graphics
} // namespace orion
#endif // RENDERTARGET_HPP_
