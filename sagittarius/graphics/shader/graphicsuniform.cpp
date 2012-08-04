/*
 * graphicsuniform.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsuniform.hpp"
#include <graphicslib>
#include <glm/transform>

#define GGNOTINITIALIZED Graphics::NotInitializedI

namespace orion {
namespace graphics {

	Uniform::Uniform()
	: id( GGNOTINITIALIZED )
	{
	}

	Uniform::Uniform( string8 name )
	: id( GGNOTINITIALIZED ),
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
		return id == GGNOTINITIALIZED;
	}

	string8 Uniform::getName() const
	{
		return name;
	}

	int Uniform::getID() const
	{
		return id;
	}

	void Uniform::set(float v)
	{
		Graphics::set( *this , v );
	}
	void Uniform::set(float v, float v2)
	{
		Graphics::set( *this , v , v2 );
	}
	void Uniform::set(float v, float v2, float v3)
	{
		Graphics::set( *this , v , v2 , v3 );
	}
	void Uniform::set(float v, float v2, float v3, float v4)
	{
		Graphics::set( *this , v , v2 , v3 , v4 );
	}
	void Uniform::setMatrix4( const float *v , int size )
	{
		Graphics::setMatrix4( *this , v , size );
	}
	void Uniform::set( const glm::mat4x4& matrix )
	{
		Graphics::set( *this , matrix );
	}
	void Uniform::set( const glm::vec2& vec )
	{
		Graphics::set( *this , vec );
	}
	void Uniform::set( const glm::vec3& vec )
	{
		Graphics::set( *this , vec );
	}
	void Uniform::set( const glm::vec4& vec )
	{
		Graphics::set( *this , vec );
	}
	void Uniform::set( const glm::ivec2& vec )
	{
		Graphics::set( *this , vec );
	}
	void Uniform::set( const glm::ivec3& vec )
	{
		Graphics::set( *this , vec );
	}
	void Uniform::set( const glm::ivec4& vec )
	{
		Graphics::set( *this , vec );
	}

	void Uniform::set( const TextureUnit& texture )
	{
		Graphics::set( *this , texture );
	}
} // namespace graphics
} // namespace orion

#undef GGNOTINITIALIZED


