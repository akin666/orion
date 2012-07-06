/*
 * application.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "application.hpp"


Application::Application()
{
}

Application::~Application()
{
}

bool Application::initialize( StringSet& args )
{
	return true;
}

bool Application::stillRunning()
{
	return true;
}

bool Application::handle( const ApplicationEvent& event )
{
	return true;
}

void Application::handleException( const std::exception& exeption )
{
}

