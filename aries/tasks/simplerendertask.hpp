/*
 * simplerendertask.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef SIMPLERENDERTASK_HPP_
#define SIMPLERENDERTASK_HPP_

#include <system/rendertask.hpp>
#include <video.hpp>

namespace orion
{

class SimpleRenderTask : public RenderTask
{
protected:
	Video *target;
public:
	SimpleRenderTask( Video *target = NULL );
	virtual ~SimpleRenderTask();

	void setVideo( Video *video );
	const Video *getVideo() const;

	virtual void run();
};

} /* namespace orion */
#endif /* SIMPLERENDERTASK_HPP_ */
