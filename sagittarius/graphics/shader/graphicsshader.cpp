/*
 * graphicsshader.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsshader.hpp"
#include <graphicslib>

#include <stdgl>

#define GGNOTINITIALIZED Graphics::NotInitialized

#define ORIONGRAPHICS_SHADER_NONE		0x0000
#define ORIONGRAPHICS_SHADER_COMPILED	0x0001

namespace orion {
namespace graphics {

	const unsigned int Shader::null = GL_NULL;

	Shader::Shader( )
	: id( null ),
	  type( ShaderUnknown ),
	  state( 0 )
	{
	}

	Shader::~Shader()
	{
		release();
	}

	void Shader::setCompiled( bool status )
	{
		status ? ( state |= ORIONGRAPHICS_SHADER_COMPILED ) : ( state &= ~ORIONGRAPHICS_SHADER_COMPILED );
	}

	void Shader::set( const string8 source )
	{
		this->source = source;
	}

	void Shader::setType( ShaderType type )
	{
		this->type = type;
	}

	ShaderType Shader::getType() const
	{
		return type;
	}

	uint Shader::getID() const
	{
		return id;
	}

	bool Shader::initialize()
	{
		GL_TEST_RAII;
		if( id == null )
		{
			switch( type )
			{
				case ShaderVertex :
				{
					id = glCreateShader( GL_VERTEX_SHADER );
					break;
				}
				case ShaderFragment :
				{
					id = glCreateShader( GL_FRAGMENT_SHADER );
					break;
				}
		#if defined(GL_GEOMETRY_SHADER)
				case ShaderGeometry :
				{
					id = glCreateShader( GL_GEOMETRY_SHADER );
					break;
				}
		#elif defined(GL_GEOMETRY_SHADER_EXT)
				case ShaderGeometry :
				{
					id = glCreateShader( GL_GEOMETRY_SHADER_EXT );
					break;
				}
		#endif
		#if defined(GL_TESS_CONTROL_SHADER)
				case ShaderControl :
				{
					id = glCreateShader( GL_TESS_CONTROL_SHADER );
					break;
				}
		#elif defined(GL_TESS_CONTROL_SHADER_EXT)
				case ShaderControl :
				{
					id = glCreateShader( GL_TESS_CONTROL_SHADER_EXT );
					break;
				}
		#endif
		#if defined(GL_TESS_EVALUATION_SHADER)
				case ShaderEvaluation :
				{
					id = glCreateShader( GL_TESS_EVALUATION_SHADER );
					break;
				}
		#elif defined(GL_TESS_EVALUATION_SHADER_EXT)
				case ShaderEvaluation :
				{
					id = glCreateShader( GL_TESS_EVALUATION_SHADER_EXT );
					break;
				}
		#endif
				default :
				{
					return false;
				}
			}
		}
		return initialized();
	}

	bool Shader::initialized() const
	{
		return id != null;
	}

	void Shader::compile()
	{
		setCompiled( false );

		if( id == null || source.size() < 1 )
		{
			return;
		}

		GL_TEST_RAII;
		const GLchar *dat = source.c_str();
		GLint size = source.size();

		glShaderSource( id , 1 , (const GLchar**)&dat , &size );
		glCompileShader( id );

		GLint status;
		glGetShaderiv( id , GL_COMPILE_STATUS , &status );

		setCompiled( status == GL_TRUE );
	}

	bool Shader::compiled() const
	{
		return (state & ORIONGRAPHICS_SHADER_COMPILED) != 0;
	}

	void Shader::release()
	{
		if( initialized() )
		{
			GL_TEST_RAII;
			glDeleteShader( id );
			id = null;
		}
	}

	bool Shader::hasError() const
	{
		if( !initialized() )
		{
			return true;
		}


		GL_TEST_RAII;

		GLint status;
		glGetShaderiv( id , GL_COMPILE_STATUS , &status );

		return status != GL_TRUE;
	}

	string8 Shader::getError() const
	{
		if( !initialized() )
		{
			return "Shader not initialized.";
		}

		GL_TEST_RAII;

		GLint loglen = 0;
		glGetShaderiv( id  , GL_INFO_LOG_LENGTH , &loglen );

		if (loglen > 0)
		{
			std::vector<GLchar> msg;
			msg.resize( loglen );

			glGetShaderInfoLog( id , loglen , NULL , &(msg[0]) );

			return std::string( &(msg[0]) );
		}
		return "";
	}

/*	void Shader::setTypeString( string8 type )
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
	}*/

} // namespace graphics
} // namespace orion

#undef GGNOTINITIALIZED
