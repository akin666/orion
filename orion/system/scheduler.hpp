/*
 * scheduler.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 *    [state task logic]                    <| full
 *      [LogicTask]			<| single		 | -
 *      [SimulationTask]	 | tick			 | game
 *      [EventTask]			<| simulation	 | simulation
 *    [RenderTask]							<| frame
 *
 */

#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include "logictask.hpp"
#include "simulationtask.hpp"
#include "eventtask.hpp"
#include "rendertask.hpp"
#include <state/statestack.hpp>
#include <orion>
#include "actionqueue.hpp"
#include <video/video.hpp>

namespace orion {

class Scheduler : public StateStack
{
protected:
	typedef std::vector<LogicTask*> LogicSet;
	typedef std::vector<SimulationTask*> SimulationSet;
	typedef std::vector<EventTaskInterface*> EventSet;
	typedef std::vector<RenderTask*> RenderSet;

	LogicSet logicTasks;
	SimulationSet simulationTasks;
	EventSet eventTasks;
	RenderSet renderTasks;

	Tick current;
	Tick nextRender;

	ActionQueue actionQueu;

	Video *video;
public:
	Scheduler();
	virtual ~Scheduler();

	void set( Video *video );

	Tick getCurrent() const;
	void setRenderTick( Tick tick );
	Tick getRenderTick( ) const;

	void add( LogicTask *task );
	void add( SimulationTask *task );
	void add( EventTaskInterface *task );
	void add( RenderTask *task );

	void schedule( Tick time , Action *action );

	void remove( LogicTask *task );
	void remove( SimulationTask *task );
	void remove( EventTaskInterface *task );
	void remove( RenderTask *task );

	void run();
};

} // namespace orion
#endif // SCHEDULER_HPP_
