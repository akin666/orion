/*
 * graphicsprogram.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsprogram.hpp"

#include <graphicslib>
#include "graphicsattribute.hpp"
#include "graphicsuniform.hpp"
#include "graphicsshader.hpp"

#define GGNOTINITIALIZED Graphics::NotInitialized

#define ORIONGRAPHICS_PROGRAM_NONE		0x0000
#define ORIONGRAPHICS_PROGRAM_LINKED	0x0001

namespace orion {
namespace graphics {

	Program::Program()
	: id( GGNOTINITIALIZED ),
	  state( ORIONGRAPHICS_PROGRAM_NONE )
	{
	}

	Program::~Program()
	{
		release();
	}

	void Program::setLinking( bool val )
	{
		val ? (state |= ORIONGRAPHICS_PROGRAM_LINKED) : (state &= ~ORIONGRAPHICS_PROGRAM_LINKED);
	}

	uint Program::getID() const
	{
		return id;
	}

	bool Program::initialize()
	{
		if( !initialized() )
		{
			Graphics::generateProgramID( 1 , &id );
			setLinking( false );

			return true;
		}
		return false;
	}

	bool Program::initialized() const
	{
		return id != GGNOTINITIALIZED;
	}

	void Program::release()
	{
		if( initialized() )
		{
			Graphics::releaseProgramID( 1 , &id );
		}
	}

	Attribute Program::getAttribute( const string8 key ) const
	{
		return Graphics::getAttribute( *this , key );
	}

	Uniform Program::getUniform( const string8 key ) const
	{
		return Graphics::getUniform( *this , key );
	}

	void Program::bind() const
	{
		Graphics::bind( *this );
	}

	void Program::bindDefault()
	{
		Graphics::bindDefaultProgram();
	}

	void Program::attach( const Shader& piece )
	{
		Graphics::bind( *this , piece );
		setLinking( false );
	}

	void Program::detach( const Shader& piece )
	{
		Graphics::unbind( *this , piece );
	}

	void Program::link()
	{
		if( Graphics::link( *this ) )
		{
			setLinking( true );
		}
		else
		{
			setLinking( false );
		}
	}

	bool Program::hasError() const
	{
		if( !initialized() )
		{
			return true;
		}
		return Graphics::hasError( *this );
	}

	string8 Program::getError() const
	{
		if( !initialized() )
		{
			return "Program not initialized.";
		}
		return Graphics::getError( *this );
	}

	bool Program::linked() const
	{
		if( !initialized() )
		{
			return false;
		}
		return (state & ORIONGRAPHICS_PROGRAM_LINKED) != 0;
	}

} // namespace graphics
} // namespace orion

#undef GGNOTINITIALIZED
