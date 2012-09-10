/*
 * graphicsprogram.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsprogram.hpp"

#include "graphicsattribute.hpp"
#include "graphicsuniform.hpp"
#include "graphicsshader.hpp"
#include <stdgl>

#define ORIONGRAPHICS_PROGRAM_NONE		0x0000
#define ORIONGRAPHICS_PROGRAM_LINKED	0x0001

namespace orion {
namespace graphics {

	const unsigned int Program::null = GL_NULL;

	Program::Program()
	: id( null ),
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
			GL_TEST_RAII;
			id = glCreateProgram();

			setLinking( false );

			return true;
		}
		return false;
	}

	bool Program::initialized() const
	{
		return id != null;
	}

	void Program::release()
	{
		if( initialized() )
		{
			GL_TEST_RAII;
			glDeleteProgram( id );
			id = null;
		}
	}

	Attribute Program::getAttribute( const string8 key ) const
	{
		GL_TEST_RAII;
		if( hasError() )
		{
			return graphics::Attribute( key );
		}

		sint aid = glGetAttribLocation( id , (const GLchar*)key.c_str() );

		// Not found?
		if( aid == graphics::Attribute::null )
		{
			return graphics::Attribute( key );
		}

		return graphics::Attribute( aid , key );
	}

	Uniform Program::getUniform( const string8 key ) const
	{
		GL_TEST_RAII;
		if( hasError() )
		{
			return graphics::Uniform( key );
		}

		sint uid = glGetUniformLocation( id , (const GLchar*)key.c_str() );

		// Not found?
		if( uid == graphics::Uniform::null )
		{
			return graphics::Uniform( key );
		}

		return graphics::Uniform( uid , key );
	}

	void Program::bind() const
	{
		GL_TEST_RAII;
		glUseProgram( id );
	}

	void Program::bindDefault()
	{
		GL_TEST_RAII;
		glUseProgram( GL_NULL );
	}

	void Program::attach( const Shader& piece )
	{
		GL_TEST_RAII;
	    glAttachShader( id , piece.getID() );
		setLinking( false );
	}

	void Program::detach( const Shader& piece )
	{
		GL_TEST_RAII;
		glDetachShader( id , piece.getID() );
	}

	void Program::link()
	{
		GL_TEST_RAII;
	    glLinkProgram( id );

	    GLint tmp;
	    glGetProgramiv( id , GL_LINK_STATUS , &tmp );

		if( tmp == GL_TRUE )
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

		GL_TEST_RAII;
		GLint loglen = 0;
		glGetProgramiv( id , GL_INFO_LOG_LENGTH , &loglen );

		return loglen > 0;
	}

	string8 Program::getError() const
	{
		if( !initialized() )
		{
			return "Program not initialized.";
		}


		GL_TEST_RAII;
		GLint loglen = 0;
		glGetProgramiv( id , GL_INFO_LOG_LENGTH , &loglen );

		if (loglen > 0)
		{
			std::vector<GLchar> msg;
			msg.resize( loglen );

			glGetProgramInfoLog( id , loglen , NULL , &(msg[0]) );

			return std::string( &(msg[0]) );
		}

		return "";
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
