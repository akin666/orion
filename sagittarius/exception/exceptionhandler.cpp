
#include "exceptionhandler.hpp"
#include <orion>

namespace orion
{

ExceptionHandler::ExceptionHandler()
{
	setGlobal<ExceptionHandler>( this );
}

ExceptionHandler::~ExceptionHandler()
{
	setGlobal<ExceptionHandler>( NULL );
}

void ExceptionHandler::handleException( const std::exception& exeption )
{
	// The default behavior is GOOD to have.
	// This means, you do not need to write the exception handling right away.
	// But also, important note is, that it actually reports something, somewhere.
	LOG->error( "Received unhandled exception!! %s " , exeption.what() );
}

} // namespace orion
