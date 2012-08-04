/*
 * graphicslib.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "sdl_detect.hpp"
#ifdef SDL_PLATFORM

#include <graphicslib>
#include <stdgl>

namespace orion {

uint Graphics::NotInitialized = GL_NULL;
int Graphics::NotInitializedI = -1;

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::bindScreen()
{
	GL_TEST_RAII;
	glBindFramebuffer( GL_FRAMEBUFFER , GL_NULL );
}

void Graphics::finish()
{
	GL_TEST_RAII;
	glFinish();
}

// Textures
void Graphics::generateTextureID( int count , uint *id )
{
	GL_TEST_RAII;
	glGenTextures( count , id );
}

void Graphics::releaseTextureID( int count , uint *id )
{
	GL_TEST_RAII;
	glDeleteTextures( count , id );
	for( int i = count -1 ; i >= 0 ; --i )
	{
		id[i] = NotInitialized;
	}
}

// TextureUnits
uint Graphics::getMaxTextureUnits()
{
	GL_TEST_RAII;
	int count;
	glGetIntegerv( GL_MAX_TEXTURE_UNITS , &count );
	return count;
}

void Graphics::bind( const graphics::TextureUnit& unit , const graphics::Texture& texture )
{
	GL_TEST_RAII;
	// Bind the texture
	glActiveTexture( GL_TEXTURE0 + unit.getID() );
	glBindTexture(GL_TEXTURE_2D, texture.getID() );
}

void Graphics::unbind( const graphics::TextureUnit& unit )
{
	GL_TEST_RAII;
	// Bind the texture
	glActiveTexture( GL_TEXTURE0 + unit.getID() );
	glBindTexture(GL_TEXTURE_2D, GL_NULL );
}

//// FrameBuffer Objects
//// Buffers (vbo/ibo/pbo)

//// Shader
////- Program
void tryCreatingProgram( uint &id )
{
	if( id == GL_NULL )
	{
		id = glCreateProgram();
	}
}

void Graphics::generateProgramID( int count , uint *id )
{
	GL_TEST_RAII;
	for( int i = count -1 ; i >= 0 ; --i )
	{
		id[i] = glCreateProgram();
	}
}

void Graphics::releaseProgramID( int count , uint *id )
{
	GL_TEST_RAII;
	for( int i = count -1 ; i >= 0 ; --i )
	{
		glDeleteProgram( id[i] );
		id[i] = NotInitialized;
	}
}

void Graphics::bind( const graphics::Program& program )
{
	GL_TEST_RAII;
	glUseProgram( program.getID() );
}

void Graphics::bindDefaultProgram()
{
	GL_TEST_RAII;
	glUseProgram( GL_NULL );
}

void Graphics::bind( const graphics::Program& program , const graphics::Shader& piece )
{
	GL_TEST_RAII;

    glAttachShader( program.getID() , piece.getID() );
}

void Graphics::unbind( const graphics::Program& program , const graphics::Shader& piece )
{
	GL_TEST_RAII;

	glDetachShader( program.getID() , piece.getID() );
}

bool Graphics::link( const graphics::Program& program )
{
	GL_TEST_RAII;

    glLinkProgram( program.getID() );

    GLint tmp;
    glGetProgramiv( program.getID() , GL_LINK_STATUS , &tmp );

    return (tmp == GL_TRUE);
}

bool Graphics::hasError( const graphics::Program& program )
{
	GL_TEST_RAII;
	GLint loglen = 0;
	glGetProgramiv( program.getID() , GL_INFO_LOG_LENGTH , &loglen );

	return loglen > 0;
}

string8 Graphics::getError( const graphics::Program& program )
{
	GL_TEST_RAII;
	GLint loglen = 0;
	glGetProgramiv( program.getID() , GL_INFO_LOG_LENGTH , &loglen );

	if (loglen > 0)
	{
		std::vector<GLchar> msg;
		msg.resize( loglen );

		glGetProgramInfoLog( program.getID() , loglen , NULL , &(msg[0]) );

		return std::string( &(msg[0]) );
	}

	return "";
}


////- Shader
void Graphics::generateShaderID( ShaderType type , uint& id )
{
	GL_TEST_RAII;
	if( id == NotInitialized )
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
				return;
			}
		}
	}
}

void Graphics::releaseShaderID( uint& id )
{
	GL_TEST_RAII;
}

bool Graphics::compileShader( const graphics::Shader& shader , const string8& source )
{
	GL_TEST_RAII;
	if( shader.getID() == NotInitialized || source.size() < 1 )
	{
		return false;
	}

	const GLchar *dat = source.c_str();
	GLint size = source.size();

	glShaderSource( shader.getID() , 1 , (const GLchar**)&dat , &size );

	glCompileShader( shader.getID() );

	GLint status;
	glGetShaderiv( shader.getID() , GL_COMPILE_STATUS , &status );

	if( status != GL_TRUE )
	{
		return false;
	}
	return true;
}

bool Graphics::hasError( const graphics::Shader& shader )
{
	GL_TEST_RAII;

	GLint status;
	glGetShaderiv( shader.getID() , GL_COMPILE_STATUS , &status );
	if( status != GL_TRUE )
	{
		return false;
	}
	return true;
}

string8 Graphics::getError( const graphics::Shader& shader )
{
	GL_TEST_RAII;

	GLint loglen = 0;
	glGetShaderiv( shader.getID()  , GL_INFO_LOG_LENGTH , &loglen );

	if (loglen > 0)
	{
		std::vector<GLchar> msg;
		msg.resize( loglen );

		glGetShaderInfoLog( shader.getID() , loglen , NULL , &(msg[0]) );

		return std::string( &(msg[0]) );
	}
	return "";
}


////- Uniforms
graphics::Uniform Graphics::getUniform( const graphics::Program& program , const string8& key )
{
	GL_TEST_RAII;
	if( program.hasError() )
	{
		return graphics::Uniform( key );
	}

	uint id = glGetUniformLocation( program.getID() , (const GLchar*)key.c_str() );

	// Not found?
	if( id == -1 )
	{
		return graphics::Uniform( key );
	}

	return graphics::Uniform( id , key );
}

void Graphics::setMatrix4( const graphics::Uniform& u , const float *v , int size )
{
	GL_TEST_RAII;
	glUniformMatrix4fv( u.getID() , size , GL_FALSE , v );
}

void Graphics::set( const graphics::Uniform& u , float v )
{
	GL_TEST_RAII;
	glUniform1f( u.getID() , v );
}

void Graphics::set( const graphics::Uniform& u , float v , float v2 )
{
	GL_TEST_RAII;
	glUniform2f( u.getID() , v , v2 );
}

void Graphics::set( const graphics::Uniform& u , float v , float v2 , float v3 )
{
	GL_TEST_RAII;
	glUniform3f( u.getID() , v , v2 , v3 );
}

void Graphics::set( const graphics::Uniform& u , float v , float v2 , float v3 , float v4 )
{
	GL_TEST_RAII;
	glUniform4f( u.getID() , v , v2 , v3 , v4 );
}


void Graphics::set( const graphics::Uniform& u , const glm::mat4x4& matrix )
{
	GL_TEST_RAII;
	glUniformMatrix4fv( u.getID() , 1 , GL_FALSE , &matrix[0][0] );
}

void Graphics::set( const graphics::Uniform& u , const glm::vec2& vec )
{
	GL_TEST_RAII;
	glUniform2f( u.getID() , vec.x , vec.y );
}

void Graphics::set( const graphics::Uniform& u , const glm::vec3& vec )
{
	GL_TEST_RAII;
	glUniform3f( u.getID() , vec.x , vec.y , vec.z );
}

void Graphics::set( const graphics::Uniform& u , const glm::vec4& vec )
{
	GL_TEST_RAII;
	glUniform4f( u.getID() , vec.x , vec.y , vec.z , vec.w );
}

void Graphics::set( const graphics::Uniform& u , const glm::ivec2& vec )
{
	GL_TEST_RAII;
	glUniform2i( u.getID() , vec.x , vec.y );
}

void Graphics::set( const graphics::Uniform& u , const glm::ivec3& vec )
{
	GL_TEST_RAII;
	glUniform3i( u.getID() , vec.x , vec.y , vec.z );
}

void Graphics::set( const graphics::Uniform& u , const glm::ivec4& vec )
{
	GL_TEST_RAII;
	glUniform4i( u.getID() , vec.x , vec.y , vec.z , vec.w );
}

void Graphics::set( const graphics::Uniform& u , const graphics::TextureUnit& texture )
{
	GL_TEST_RAII;
	glUniform1i( u.getID(), texture.getID() );
}


////- Attributes
graphics::Attribute Graphics::getAttribute( const graphics::Program& program , const string8& key )
{
	GL_TEST_RAII;
	if( program.hasError() )
	{
		return graphics::Attribute( key );
	}

	uint id = glGetAttribLocation( program.getID() , (const GLchar*)key.c_str() );

	// Not found?
	if( id == -1 )
	{
		return graphics::Attribute( key );
	}

	return graphics::Attribute( id , key );
}

void Graphics::enable( const graphics::Attribute& attribute )
{
	GL_TEST_RAII;
	glEnableVertexAttribArray( attribute.getID() );
}

void Graphics::disable( const graphics::Attribute& attribute )
{
	GL_TEST_RAII;
	glDisableVertexAttribArray( attribute.getID() );
}

} // orion

#endif // SDL_PLATFORM
