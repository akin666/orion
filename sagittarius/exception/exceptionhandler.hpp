
#ifndef EXCEPTIONHANDLER_HPP_
#define EXCEPTIONHANDLER_HPP_

#include <exception>
#include <orion>

namespace orion
{

class ExceptionHandler
{
public:
	ExceptionHandler();
	virtual ~ExceptionHandler();

	virtual void handleException( const std::exception& exeption );
	virtual void handleEllipsisException();
};

} // namespace orion
#endif
