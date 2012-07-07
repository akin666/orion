/*
 * application.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "application.hpp"
#include <video/video.hpp>
#include <tasks/simplerendertask.hpp>

using namespace orion;

Application::Application()
: running( true )
{
}

Application::~Application()
{
}

bool Application::initialize( StringSet& args )
{
	// get main screen.
	Video *video = Global<Video>::get();

	// init renderer & send it to scheduler.
	RenderTask *renderer = new SimpleRenderTask( video );
	Global<Scheduler>::get()->add( renderer );

	running = true;

	return true;
}

bool Application::stillRunning()
{
	return true;
}

bool Application::handle( const ApplicationEvent& event )
{
	switch( event.type )
	{
		case ApplicationEvent::Quit :
		{
			running = false;
			break;
		}
		default:
		{
			break;
		}
	}
	return true;
}

void Application::handleException( const std::exception& exeption )
{
}

