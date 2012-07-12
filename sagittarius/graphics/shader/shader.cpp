/*
 * shader.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "shader.hpp"
#include <stdexcept>

namespace orion {
namespace graphics {

	Shader::Shader( )
	: id( GL_NULL ),
	  m_type( UNKNOWN ),
	  state( 0 )
	{
	}

	Shader::~Shader()
	{
		try {
			reset();
		} catch( ... ) {
			// ...
		}
	}

	uint state;

	void Shader::setLoaded( bool status )
	{
		if( status )
		{
			state |= LOADED;
		}
		else
		{
			state &= ~LOADED;
		}
	}

	void Shader::setCompiled( bool status )
	{
		if( status )
		{
			state |= COMPILED;
		}
		else
		{
			state &= ~COMPILED;
		}
	}

	void Shader::createId() throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		if( id == GL_NULL )
		{
			switch( m_type )
			{
				case Shader::VERTEX :
				{
					id = glCreateShader( GL_VERTEX_SHADER );
					break;
				}
				case Shader::FRAGMENT :
				{
					id = glCreateShader( GL_FRAGMENT_SHADER );
					break;
				}
		#if defined(GL_GEOMETRY_SHADER)
				case Shader::GEOMETRY :
				{
					id = glCreateShader( GL_GEOMETRY_SHADER );
					break;
				}
		#elif defined(GL_GEOMETRY_SHADER_EXT)
				case Shader::GEOMETRY :
				{
					id = glCreateShader( GL_GEOMETRY_SHADER_EXT );
					break;
				}
		#endif
		#if defined(GL_TESS_CONTROL_SHADER)
				case Shader::CONTROL :
				{
					id = glCreateShader( GL_TESS_CONTROL_SHADER );
					break;
				}
		#elif defined(GL_TESS_CONTROL_SHADER_EXT)
				case Shader::CONTROL :
				{
					id = glCreateShader( GL_TESS_CONTROL_SHADER_EXT );
					break;
				}
		#endif
		#if defined(GL_TESS_EVALUATION_SHADER)
				case Shader::EVALUATION :
				{
					id = glCreateShader( GL_TESS_EVALUATION_SHADER );
					break;
				}
		#elif defined(GL_TESS_EVALUATION_SHADER_EXT)
				case Shader::CONTROL :
				{
					id = glCreateShader( GL_TESS_EVALUATION_SHADER_EXT );
					break;
				}
		#endif
				default :
				{
					LOG_ERROR << "Requested unknown shader type: " << m_type << std::endl;
					return;
				}
			}
		}
		GL_TEST_ERROR("end")
	}

	void Shader::setType( Type type )
	{
		if( id == GL_NULL )
		{
			m_type = type;
		}
	}

	void Shader::setTypeString( string8 type )
	{
		if( type == "fragment" )
		{
			setType( FRAGMENT );
		}
		else if( type == "vertex" )
		{
			setType( VERTEX );
		}
#if defined(GL_GEOMETRY_SHADER) or defined(GL_GEOMETRY_SHADER_EXT)
		else if( type == "geometry" )
		{
			setType( GEOMETRY );
		}
#endif
#if defined(GL_TESS_CONTROL_SHADER) or defined(GL_TESS_CONTROL_SHADER_EXT)
		else if( type == "control" )
		{
			setType( CONTROL );
		}
#endif
#if defined(GL_TESS_EVALUATION_SHADER) or defined(GL_TESS_EVALUATION_SHADER_EXT)
		else if( type == "evaluation" )
		{
			setType( EVALUATION );
		}
#endif
	}

	uint Shader::getId()
	{
		return id;
	}

	Shader::Type Shader::getType()
	{
		return m_type;
	}

	char *Shader::access()
	{
		return data.access();
	}

	uint Shader::size()
	{
		return data.size();
	}

	void Shader::load() throw (std::exception)
	{
		if( data.size() == 0 )
		{
			LOG_ERROR << "Failed to load shader, no data set." << std::endl;
			throw std::exception("Failed to load shader.");
		}

		createId();

		if( id == GL_NULL )
		{
			throw std::exception("Failed to create shader id.");
		}

		setCompiled( false );

		GL_TEST_ERROR("begin")

		const GLchar *dat = data.access();
		GLint size = data.size();

		glShaderSource( id , 1 , (const GLchar**)&dat , &size );
		GL_TEST_ERROR("end")

		setLoaded( true );
	}

	void Shader::compile() throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glCompileShader( id );

		GLint tmp;
		glGetShaderiv( id , GL_COMPILE_STATUS , &tmp );

		if( tmp )
		{
			setCompiled( true );
			GL_TEST_ERROR("end")
			// ALL OK!
			return;
		}

		// ERROR!
		GLint loglen = 0;
		glGetShaderiv(id  , GL_INFO_LOG_LENGTH , &loglen );

		if (loglen > 0)
		{
			GLchar log[loglen];
			glGetShaderInfoLog( id , loglen , NULL , log );

			LOG_ERROR << "Shader compile error: " << log << std::endl;
		}
		GL_TEST_ERROR("end2")

		throw std::exception("Failed to compile shader.");
	}

	void Shader::reset() throw (std::exception)
	{
		if( id != GL_NULL )
		{
			GL_TEST_ERROR("begin")
			glDeleteShader( id );
			id = GL_NULL;
			GL_TEST_ERROR("end")
		}
		setCompiled( false );
	}

	bool Shader::isLoaded()
	{
		return (state & (LOADED | COMPILED) ) != 0;
	}

	void Shader::set( const string8& newData )
	{
		data = newData;
		setLoaded( false );
	}

} // namespace graphics
} // namespace orion

