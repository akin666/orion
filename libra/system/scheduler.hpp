/*
 * scheduler.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 *    [state stack logics]                  <| full
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
#include <video>
#include <profiler/profilerdata.hpp>

namespace orion {

class Scheduler
{
protected:
	typedef std::vector<StateStack*> StateStackSet;
	typedef std::vector<LogicTask*> LogicSet;
	typedef std::vector<SimulationTask*> SimulationSet;
	typedef std::vector<EventTaskInterface*> EventSet;
	typedef std::vector<RenderTask*> RenderSet;

	StateStackSet stateStackTasks;;
	LogicSet logicTasks;
	SimulationSet simulationTasks;
	EventSet eventTasks;
	RenderSet renderTasks;

	Tick current;
	Tick nextRender;

	ActionQueue actionQueu;

	Video *video;

	// Profilers:
	ProfilerData frame;
	ProfilerData state;
	ProfilerData tick;
	ProfilerData query;
	ProfilerData actionque;
public:
	Scheduler();
	virtual ~Scheduler();

	void set( Video *video );

	void setCurrent( Tick tick );
	Tick getCurrent() const;
	void setRenderTick( Tick tick );
	Tick getRenderTick( ) const;

	void add( StateStack *task );
	void add( LogicTask *task );
	void add( SimulationTask *task );
	void add( EventTaskInterface *task );
	void add( RenderTask *task );

	void schedule( Tick time , Action *action );

	void remove( StateStack *task );
	void remove( LogicTask *task );
	void remove( SimulationTask *task );
	void remove( EventTaskInterface *task );
	void remove( RenderTask *task );

	void run();
};

} // namespace orion
#endif // SCHEDULER_HPP_
