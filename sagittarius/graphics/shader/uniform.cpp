/*
 * uniform.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "uniform.hpp"
#include <opengl>
#include <glm/transform>
#include <stdexcept>

namespace orion {
namespace graphics {

	Uniform::Uniform()
	{
		m_program_id = GL_NULL;
	}

	Uniform::~Uniform()
	{
	}

	void Uniform::setProgram( uint program )
	{
		m_program_id = program;
	}

	void Uniform::attach( std::string name ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		m_name = name;

		m_uniform_id = glGetUniformLocation( m_program_id , (const GLchar*)name.c_str() );

		if( m_uniform_id < GL_NULL )
		{
			throw std::exception( std::string("Uniform not found ") + name );
		}

		GL_TEST_ERROR("end")
	}

	std::string Uniform::getName()
	{
		return m_name;
	}

	void Uniform::set(float v) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform1f( m_uniform_id , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(float v, float v2) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2f( m_uniform_id , v , v2 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(float v, float v2, float v3) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3f( m_uniform_id , v , v2 , v3 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(float v, float v2, float v3, float v4) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4f( m_uniform_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(int v) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform1i( m_uniform_id , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(int v, int v2) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2i( m_uniform_id , v , v2 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(int v, int v2, int v3) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3i( m_uniform_id , v , v2 , v3 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(int v, int v2, int v3, int v4) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4i( m_uniform_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(float *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform1fv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set2(float *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2fv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set3(float *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3fv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set4(float *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4fv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set(int *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform1iv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set2(int *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2iv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set3(int *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3iv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::set4(int *v, int size) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4iv( m_uniform_id , size , v );
		GL_TEST_ERROR("end")
	}
	void Uniform::setMatrix4( const float *v , int size ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniformMatrix4fv( m_uniform_id , size , GL_FALSE , v );
		GL_TEST_ERROR("end")
	}

	void Uniform::set( const glm::mat4x4& matrix ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniformMatrix4fv( m_uniform_id , 1 , GL_FALSE , &matrix[0][0] );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::vec2& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2f( m_uniform_id , vec.x , vec.y );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::vec3& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3f( m_uniform_id , vec.x , vec.y , vec.z );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::vec4& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4f( m_uniform_id , vec.x , vec.y , vec.z , vec.w );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::ivec2& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform2i( m_uniform_id , vec.x , vec.y );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::ivec3& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform3i( m_uniform_id , vec.x , vec.y , vec.z );
		GL_TEST_ERROR("end")
	}
	void Uniform::set( const glm::ivec4& vec ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		glUniform4i( m_uniform_id , vec.x , vec.y , vec.z , vec.w );
		GL_TEST_ERROR("end")
	}

	void Uniform::bindTexture( int texture_unit , uint texture_id ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		// Bind the texture
		glActiveTexture( GL_TEXTURE0 + texture_unit );
		glBindTexture(GL_TEXTURE_2D, texture_id );
		// Set the sampler texture unit
		glUniform1i(m_uniform_id, texture_unit );

		GL_TEST_ERROR("end")
	}

	void Uniform::bindTexture( const Texture& texture , int texture_unit ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		// Bind the texture
		glActiveTexture( GL_TEXTURE0 + texture_unit );
		glBindTexture(GL_TEXTURE_2D, texture.getId() );
		// Set the sampler texture unit
		glUniform1i(m_uniform_id, texture_unit );

		GL_TEST_ERROR("end")
	}

} // namespace graphics
} // namespace orion



