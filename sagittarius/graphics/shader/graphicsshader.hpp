/*
 * graphicsshader.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSSHADER_H_
#define GRAPHICSSHADER_H_

#include <orion>

namespace orion {
namespace graphics {

	class Shader
	{
	private:
		uint id;
		ShaderType type;
		string8 source;
		uint state;

		void setCompiled( bool status );
	public:
		static const unsigned int null;

		Shader();
		~Shader();

		void set( const string8 source );
		void setType( ShaderType type );
		ShaderType getType() const;

		uint getID() const;

		bool initialize();
		bool initialized() const;
		void compile();
		bool compiled() const;

		void release();

		bool hasError() const;
		string8 getError() const;
	};

} // namespace graphics
} // namespace orion


#endif // GRAPHICSSHADER_H_
