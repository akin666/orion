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
	int count = 0;
#ifndef OS_LINUX
	glGetIntegerv( GL_MAX_TEXTURE_UNITS , &count );
#endif
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

} // orion

#endif // SDL_PLATFORM
