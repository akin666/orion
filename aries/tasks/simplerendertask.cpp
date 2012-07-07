/*
 * simplerendertask.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "simplerendertask.hpp"

namespace orion
{

SimpleRenderTask::SimpleRenderTask( Video *target )
: target( target )
{
}

SimpleRenderTask::~SimpleRenderTask()
{
}

void SimpleRenderTask::setVideo( Video *video )
{
	target = video;
}

const Video *SimpleRenderTask::getVideo() const
{
	return target;
}

void SimpleRenderTask::run()
{
	if( target == NULL )
	{
		return;
	}

	// Bind screen..
	target->getRenderTarget().bind();
	target->flip();
}

} // namespace orion
