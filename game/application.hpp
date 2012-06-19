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

using namespace orion;

class Application : public ApplicationInterface
{
public:
	Application();
	virtual ~Application();

	virtual void initialize();

	virtual bool handle( const ApplicationEvent& event );

	virtual void handleException( const std::exception& exeption );
};

#endif // APPLICATION_HPP_
