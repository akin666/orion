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

	virtual void initialize() = 0;

	void run();
};

} // namespace orion
#endif // APPLICATIONINTERFACE_HPP_
