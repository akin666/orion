/*
 * graphicsrenderer.h
 *
 *  Created on: 9.9.2012
 *      Author: akin
 */

#ifndef GRAPHICSRENDERER_H_
#define GRAPHICSRENDERER_H_

namespace graphics
{

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void render() = 0;
};

} // namespace graphics
#endif // GRAPHICSRENDERER_H_
