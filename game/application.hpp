/*
 * application.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <orion>
#include <application/applicationinterface.hpp>

class Application : public orion::ApplicationInterface
{
public:
	Application();
	virtual ~Application();

	virtual bool stillRunning();

	virtual bool initialize( orion::StringSet& args );

	virtual bool handle( const orion::ApplicationEvent& event );

	virtual void handleException( const std::exception& exeption );
};

#endif // APPLICATION_HPP_
