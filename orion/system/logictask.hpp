/*
 * logictask.h
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef LOGICTASK_H_
#define LOGICTASK_H_

namespace orion {

class LogicTask {
public:
	LogicTask();
	virtual ~LogicTask();

	virtual void run() = 0;
};

} // namespace orion
#endif // LOGICTASK_H_
