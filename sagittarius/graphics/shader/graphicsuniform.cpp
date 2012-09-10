/*
 * graphicsuniform.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsuniform.hpp"
#include <glm/transform>
#include <stdgl>

namespace orion {
namespace graphics {

	const int Uniform::null = -1;

	Uniform::Uniform()
	: id( null )
	{
	}

	Uniform::Uniform( string8 name )
	: id( null ),
	  name( name )
	{
	}

	Uniform::Uniform( int id , string8 name )
	: id( id ),
	  name( name )
	{
	}

	Uniform::Uniform( const Uniform& other )
	: id( other.id ),
	  name( other.name )
	{
	}

	const Uniform& Uniform::operator = ( const Uniform& other )
	{
		id = other.id;
		name = other.name;
		return *this;
	}

	Uniform::~Uniform()
	{
		// does not own anything!
	}

	bool Uniform::hasError() const
	{
		return id == null;
	}

	const string8& Uniform::getName() const
	{
		return name;
	}

	int Uniform::getID() const
	{
		return id;
	}

	void Uniform::set(float v)
	{
		GL_TEST_RAII;
		glUniform1f( id , v );
	}
	void Uniform::set(float v, float v2)
	{
		GL_TEST_RAII;
		glUniform2f( id , v , v2 );
	}
	void Uniform::set(float v, float v2, float v3)
	{
		GL_TEST_RAII;
		glUniform3f( id , v , v2 , v3 );
	}
	void Uniform::set(float v, float v2, float v3, float v4)
	{
		GL_TEST_RAII;
		glUniform4f( id , v , v2 , v3 , v4 );
	}
	void Uniform::setMatrix4( const float *v , int size )
	{
		GL_TEST_RAII;
		glUniformMatrix4fv( id , size , GL_FALSE , v );
	}
	void Uniform::set( const glm::mat4x4& matrix )
	{
		GL_TEST_RAII;
		glUniformMatrix4fv( id , 1 , GL_FALSE , &matrix[0][0] );
	}
	void Uniform::set( const glm::vec2& vec )
	{
		GL_TEST_RAII;
		glUniform2f( id , vec.x , vec.y );
	}
	void Uniform::set( const glm::vec3& vec )
	{
		GL_TEST_RAII;
		glUniform3f( id , vec.x , vec.y , vec.z );
	}
	void Uniform::set( const glm::vec4& vec )
	{
		GL_TEST_RAII;
		glUniform4f( id , vec.x , vec.y , vec.z , vec.w );
	}
	void Uniform::set( const glm::ivec2& vec )
	{
		GL_TEST_RAII;
		glUniform2i( id , vec.x , vec.y );
	}
	void Uniform::set( const glm::ivec3& vec )
	{
		GL_TEST_RAII;
		glUniform3i( id , vec.x , vec.y , vec.z );
	}
	void Uniform::set( const glm::ivec4& vec )
	{
		GL_TEST_RAII;
		glUniform4i( id , vec.x , vec.y , vec.z , vec.w );
	}

	void Uniform::set( const TextureUnit& texture )
	{
		GL_TEST_RAII;
		glUniform1i( id , texture.getID() );
	}
} // namespace graphics
} // namespace orion



