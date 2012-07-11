/*
 * simulationtask.h
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef SIMULATIONTASK_H_
#define SIMULATIONTASK_H_

#include <profiler/profilerdata.hpp>

namespace orion {

class SimulationTask {
public:
	SimulationTask();
	virtual ~SimulationTask();

	virtual void run() = 0;

	ProfilerData profiler;
};

} // namespace orion
#endif // SIMULATIONTASK_H_
