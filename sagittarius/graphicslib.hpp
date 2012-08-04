/*
 * graphicslib.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSLIB_HPP_
#define GRAPHICSLIB_HPP_

#include <orion>
#include <graphics/graphicstextureunit.hpp>
#include <graphics/shader/graphicsprogram.hpp>
#include <graphics/shader/graphicsuniform.hpp>
#include <graphics/shader/graphicsattribute.hpp>

namespace orion {

class Graphics
{
private:
	Graphics();
	~Graphics();
public:
	static uint NotInitialized;
	static int NotInitializedI;
	// opengl quirks.. i wish, someone would do bad things to the one responsible,
	// who thought switching to INT id (from UINT id) later on is a GOOD idea.

	//// Common
	// finish all operations
	static void finish();

	//// screen.
	static void bindScreen();

	//// Texture
	static void generateTextureID( int count , uint *id );
	static void releaseTextureID( int count , uint *id );

	//// TextureUnit
	// id is in range of [0,XXX]
	static uint getMaxTextureUnits();
	static void bind( const graphics::TextureUnit& unit , const graphics::Texture& texture );
	static void unbind( const graphics::TextureUnit& unit );

	//// FrameBuffer Objects
	//// Buffers (vbo/ibo/pbo)

	//// Shader
	////- Program
	static void generateProgramID( int count , uint *id );
	static void releaseProgramID( int count , uint *id );
	static void bind( const graphics::Program& program );
	static void bindDefaultProgram();
	static void bind( const graphics::Program& program , const graphics::Shader& piece );
	static void unbind( const graphics::Program& program , const graphics::Shader& piece );
	static bool link( const graphics::Program& program );
	static bool hasError( const graphics::Program& program );
	static string8 getError( const graphics::Program& program );

	////- Shader
	static void generateShaderID( ShaderType type , uint& id );
	static void releaseShaderID( uint& id );
	static bool compileShader( const graphics::Shader& shader , const string8& source );
	static bool hasError( const graphics::Shader& shader );
	static string8 getError( const graphics::Shader& shader );

	////- Uniforms
	static graphics::Uniform getUniform( const graphics::Program& program , const string8& key );

	static void setMatrix4( const graphics::Uniform& u , const float *v , int size );
	static void set( const graphics::Uniform& u , float v );
	static void set( const graphics::Uniform& u , float v , float v2 );
	static void set( const graphics::Uniform& u , float v , float v2 , float v3 );
	static void set( const graphics::Uniform& u , float v , float v2 , float v3 , float v4 );

	static void set( const graphics::Uniform& u , const glm::mat4x4& matrix );
	static void set( const graphics::Uniform& u , const glm::vec2& vec );
	static void set( const graphics::Uniform& u , const glm::vec3& vec );
	static void set( const graphics::Uniform& u , const glm::vec4& vec );
	static void set( const graphics::Uniform& u , const glm::ivec2& vec );
	static void set( const graphics::Uniform& u , const glm::ivec3& vec );
	static void set( const graphics::Uniform& u , const glm::ivec4& vec );
	static void set( const graphics::Uniform& u , const graphics::TextureUnit& texture );

	////- Attributes
	static graphics::Attribute getAttribute( const graphics::Program& program , const string8& key );
	static void enable( const graphics::Attribute& attribute );
	static void disable( const graphics::Attribute& attribute );
};

} // orion

#endif // GRAPHICSLIB_HPP_
