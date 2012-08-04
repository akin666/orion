/*
 * graphicsshader.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsshader.hpp"
#include <graphicslib>

#define GGNOTINITIALIZED Graphics::NotInitialized

#define ORIONGRAPHICS_SHADER_NONE		0x0000
#define ORIONGRAPHICS_SHADER_COMPILED	0x0001

namespace orion {
namespace graphics {

	Shader::Shader( )
	: id( GGNOTINITIALIZED ),
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
		Graphics::generateShaderID( type , id );

		return initialized();
	}

	bool Shader::initialized() const
	{
		return id != GGNOTINITIALIZED;
	}

	void Shader::compile()
	{
		setCompiled( false );
		if( Graphics::compileShader( *this , source ) )
		{
			setCompiled( true );
		}
	}

	bool Shader::compiled() const
	{
		return (state & ORIONGRAPHICS_SHADER_COMPILED) != 0;
	}

	void Shader::release()
	{
		if( initialized() )
		{
			Graphics::releaseShaderID( id );
		}
	}

	bool Shader::hasError() const
	{
		if( !initialized() )
		{
			return true;
		}
		return Graphics::hasError( *this );
	}

	string8 Shader::getError() const
	{
		if( !initialized() )
		{
			return "Shader not initialized.";
		}
		return Graphics::getError( *this );
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
