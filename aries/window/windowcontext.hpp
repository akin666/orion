/*
 * windowcontext.hpp
 *
 *  Created on: 19.6.2012
 *      Author: akin
 */

#ifndef WINDOWCONTEXT_HPP_
#define WINDOWCONTEXT_HPP_

#include <graphics/rendertarget/rendertarget.hpp>
#include <graphics/rendertarget/rendersetting.hpp>

namespace orion {

class WindowContext {
public:
	WindowContext() {}
	virtual ~WindowContext() {}

	virtual void populate( RenderSettingSet& supported ) = 0;
	virtual RenderSetting getSettings() const = 0;
	virtual bool apply( const RenderSetting& res ) = 0;

	virtual RenderTarget& getRenderTarget() = 0;
};

} // namespace orion
#endif // WINDOWCONTEXT_HPP_
