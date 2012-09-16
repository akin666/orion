/*
 * rendertarget.hpp
 *
 *  Created on: 12.9.2012
 *      Author: akin
 */

#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include "renderrenderer.hpp"
#include "renderrenderable.hpp"
#include "renderprogram.hpp"

namespace render
{

class Target
{
public:
	virtual ~Target()
	{
	}

	virtual void clear() = 0;
	virtual void render( const Renderer& renderer , const Program& program , const Renderable& renderable ) = 0;
};

} // namespace render
#endif // RENDERTARGET_HPP_
