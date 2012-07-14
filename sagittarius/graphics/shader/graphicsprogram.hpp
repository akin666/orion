/*
 * graphicsprogram.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSPROGRAM_H_
#define GRAPHICSPROGRAM_H_

#include <orion>
#include "graphicsuniform.hpp"
#include "graphicsattribute.hpp"
#include "graphicsshader.hpp"

namespace orion {
namespace graphics {

	class Program
	{
	protected:
		uint id;
		uint state;

		void setLinking( bool val );
	public:
		Program();
		virtual ~Program();

		uint getID() const;

		bool initialize();
		bool initialized() const;
		void release();

		Attribute getAttribute( const string8 key ) const;
		Uniform getUniform( const string8 key ) const;

		void bind() const;
		static void bindDefault();

		void attach( const Shader& piece );
		void detach( const Shader& piece );
		void link();

		bool hasError() const;
		string8 getError() const;
		bool linked() const;
	};

} // namespace graphics
} // namespace orion


#endif // GRAPHICSPROGRAM_H_
