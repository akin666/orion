/*
 * application.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "application.hpp"
#include <video>
#include <tasks/simplerendertask.hpp>
#include "menustate.hpp"
#include <allocator>

#include <resource/resourcemanager.hpp>
#include <resource/textureresource.hpp>

#include <system/scheduler.hpp>

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

	// init application statestack and send it to scheduler.
	Global<Scheduler>::get()->push( applicationStates );

	// push the first state into application statestack.
	applicationStates.push<MenuState>();

	// request loading of logo resource.
	loadResource<TextureResource>( "logo" , "data/logo.png" );

	running = true;

	return true;
}

bool Application::stillRunning()
{
	return running;
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

