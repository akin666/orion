/*
 * scheduler.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "scheduler.hpp"
#include <exception/exceptionhandler.hpp>
#include <native>

namespace orion {

Scheduler::Scheduler()
: current( 0 ),
  nextRender( 1 ),
  video( NULL )
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::set( Video *video )
{
	this->video = video;
}

void Scheduler::setCurrent( Tick tick )
{
	current = tick;
}

Tick Scheduler::getCurrent() const
{
	return current;
}

void Scheduler::setRenderTick( Tick tick )
{
	nextRender = tick;
}

Tick Scheduler::getRenderTick( ) const
{
	return nextRender;
}

void Scheduler::add( LogicTask *task )
{
	logicTasks.push_back( task );
}

void Scheduler::add( SimulationTask *task )
{
	simulationTasks.push_back( task );
}

void Scheduler::add( EventTaskInterface *task )
{
	eventTasks.push_back( task );
}

void Scheduler::add( RenderTask *task )
{
	renderTasks.push_back( task );
}

void Scheduler::schedule( Tick time , Action *action )
{
	actionQueu.add( time , action );
}

void Scheduler::remove( LogicTask *task )
{
	for( LogicSet::iterator iter = logicTasks.begin() ; iter != logicTasks.end() ; ++iter )
	{
		if( *iter == task )
		{
			logicTasks.erase( iter );
			return;
		}
	}
}

void Scheduler::remove( SimulationTask *task )
{
	for( SimulationSet::iterator iter = simulationTasks.begin() ; iter != simulationTasks.end() ; ++iter )
	{
		if( *iter == task )
		{
			simulationTasks.erase( iter );
			return;
		}
	}
}

void Scheduler::remove( EventTaskInterface *task )
{
	for( EventSet::iterator iter = eventTasks.begin() ; iter != eventTasks.end() ; ++iter )
	{
		if( *iter == task )
		{
			eventTasks.erase( iter );
			return;
		}
	}
}

void Scheduler::remove( RenderTask *task )
{
	for( RenderSet::iterator iter = renderTasks.begin() ; iter != renderTasks.end() ; ++iter )
	{
		if( *iter == task )
		{
			renderTasks.erase( iter );
			return;
		}
	}
}

void Scheduler::run()
{
	// Tick simulation.
	// Catch the real-time.
	try
	{ // frame
		ProfilerRAII frameProfiler( frame );
		{ // state
			ProfilerRAII stateProfiler( state );
			runStateStack();
		}
		for( ; current < nextRender ; ++current )
		{ // tick
			ProfilerRAII tickProfiler( tick );

			// Query platform for input or whatever.
			if( video != NULL )
			{ // Query
				ProfilerRAII queryProfiler( query );
				video->query();
			}

			{ // actionque
				ProfilerRAII queryProfiler( actionque );
				// Fire up TICK based actions
				actionQueu.run( current );
			}

			// Resolve events for this TICK (this means joystick key etc. events are handled just before logic)
			for( EventSet::iterator iter = eventTasks.begin() ; iter != eventTasks.end() ; ++iter )
			{
				ProfilerRAII profiler( (*iter)->profiler );
				(*iter)->run();
			}

			// Logical tasks are run.
			for( LogicSet::iterator iter = logicTasks.begin() ; iter != logicTasks.end() ; ++iter )
			{
				ProfilerRAII profiler( (*iter)->profiler );
				(*iter)->run();
			}

			// Simulation tasks are run.
			for( SimulationSet::iterator iter = simulationTasks.begin() ; iter != simulationTasks.end() ; ++iter )
			{
				ProfilerRAII profiler( (*iter)->profiler );
				(*iter)->run();
			}
		} // tick
		for( RenderSet::iterator iter = renderTasks.begin() ; iter != renderTasks.end() ; ++iter )
		{
			ProfilerRAII profiler( (*iter)->profiler );
			(*iter)->run();
		}
	}
	catch( std::exception& e )
	{
		ExceptionHandler *handler = getGlobal<ExceptionHandler>();
		if( handler != NULL )
		{
			handler->handleException( e );
		}
	}
	catch( ... )
	{
		// What to do?
	}
}

} // namespace orion
