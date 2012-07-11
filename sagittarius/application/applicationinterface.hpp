/*
 * applicationinterface.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef APPLICATIONINTERFACE_HPP_
#define APPLICATIONINTERFACE_HPP_

#include <orionevent>
#include <exception/exceptionhandler.hpp>

namespace orion {

class ApplicationInterface : public EventListener< ApplicationEvent >, public ExceptionHandler
{
public:
	ApplicationInterface();
	virtual ~ApplicationInterface();

	virtual bool stillRunning() = 0;
	virtual bool initialize( StringSet& args ) = 0;
};

} // namespace orion
#endif // APPLICATIONINTERFACE_HPP_
