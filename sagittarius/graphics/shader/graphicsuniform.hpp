/*
 * graphicsuniform.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSUNIFORM_H_
#define GRAPHICSUNIFORM_H_

#include <orion>
#include <graphics/graphicstextureunit.hpp>

namespace orion {
namespace graphics {

	class Program;
	class Uniform
	{
	protected:
		int id;
		string8 name;
	public:
		// Creates an Uniform, in 'error' state
		Uniform();
		Uniform( string8 name );
		// Possibility of creating Uniform in non error state.
		Uniform( int id , string8 name );
		// Copies the Uniform indicated, whether it is in error or not.
		Uniform( const Uniform& other );
		virtual ~Uniform();

		const Uniform& operator = ( const Uniform& other );

		bool hasError() const;
		string8 getName() const;
		int getID() const;

		void set( float v );
		void set( float v , float v2 );
		void set( float v , float v2 , float v3 );
		void set( float v , float v2 , float v3 , float v4 );

		void setMatrix4( const float *v , int size );

		void set( const glm::mat4x4& matrix );
		void set( const glm::vec2& vec );
		void set( const glm::vec3& vec );
		void set( const glm::vec4& vec );
		void set( const glm::ivec2& vec );
		void set( const glm::ivec3& vec );
		void set( const glm::ivec4& vec );

		void set( const TextureUnit& texture );
	};

} // namespace graphics
} // namespace orion


#endif // GRAPHICSUNIFORM_H_
