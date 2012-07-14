/*
 * graphicsattribute.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef GRAPHICSATTRIBUTE_H_
#define GRAPHICSATTRIBUTE_H_

#include <orion>

namespace orion {
namespace graphics {

	class Attribute
	{
	protected:
		int id;
		string8 name;
	public:
		// Creates an attribute, in 'error' state
		Attribute();
		Attribute( string8 name );
		// Possibility of creating attribute in non error state.
		Attribute( int id , string8 name );
		// Copies the attribute indicated, whether it is in error or not.
		Attribute( const Attribute& other );
		virtual ~Attribute();

		const Attribute& operator = ( const Attribute& other );

		bool hasError() const;
		string8 getName() const;
		int getID() const;

		void enable();
		void disable();
// TODO!
//		void setPointer( int size , GLenum type , void *ptr );
//		void setPointer( int data_size , GLenum data_type , GLsizei stride );
	};

} // namespace graphics
} // namespace orion

#endif // GRAPHICSATTRIBUTE_H_
