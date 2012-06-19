/*
 * rendertask.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef RENDERTASK_HPP_
#define RENDERTASK_HPP_

namespace orion {

class RenderTask {
public:
	RenderTask();
	virtual ~RenderTask();

	virtual void run() = 0;
};

} // namespace orion
#endif // RENDERTASK_HPP_
