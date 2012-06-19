/*
 * scheduler.cpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#include "scheduler.hpp"
#include <exception/exceptionhandler.hpp>

namespace orion {

Scheduler::Scheduler()
: current( 0 ),
  nextRender( 1 )
{
}

Scheduler::~Scheduler()
{
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
	{
		runStateStack();
		for( ; current < nextRender ; ++current )
		{
			for( LogicSet::iterator iter = logicTasks.begin() ; iter != logicTasks.end() ; ++iter )
			{
				(*iter)->run();
			}
			for( SimulationSet::iterator iter = simulationTasks.begin() ; iter != simulationTasks.end() ; ++iter )
			{
				(*iter)->run();
			}
			for( EventSet::iterator iter = eventTasks.begin() ; iter != eventTasks.end() ; ++iter )
			{
				(*iter)->run();
			}
		}
		// Render
		for( RenderSet::iterator iter = renderTasks.begin() ; iter != renderTasks.end() ; ++iter )
		{
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
