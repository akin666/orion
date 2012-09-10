/*
 * graphicsattribute.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "graphicsattribute.hpp"
#include <stdgl>

namespace orion {
namespace graphics {

	const int Attribute::null = -1;

	Attribute::Attribute()
	: id( null )
	{
	}

	Attribute::Attribute( string8 name )
	: id( null ),
	  name( name )
	{
	}

	Attribute::Attribute( int id , string8 name )
	: id( id ),
	  name( name )
	{
	}

	Attribute::Attribute( const Attribute& other )
	: id( other.id ),
	  name( other.name )
	{
	}

	const Attribute& Attribute::operator = ( const Attribute& other )
	{
		id = other.id;
		name = other.name;
		return *this;
	}

	Attribute::~Attribute()
	{
		// does not own anything!
	}

	bool Attribute::hasError() const
	{
		return id == null;
	}

	const string8& Attribute::getName() const
	{
		return name;
	}

	int Attribute::getID() const
	{
		return id;
	}

	void Attribute::enable()
	{
		GL_TEST_RAII;
		glEnableVertexAttribArray( id );
	}

	void Attribute::disable()
	{
		GL_TEST_RAII;
		glDisableVertexAttribArray( id );
	}
/*
	void Attribute::setPointer( int data_size , GLenum data_type , GLsizei stride )
	{
		//glEnableVertexAttribArray(0);
		//We like submitting vertices on stream 0 for no special reason //The starting point of the VBO, for the vertices
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(0));
		//glEnableVertexAttribArray(1);
		//We like submitting normals on stream 1 for no special reason //The starting point of normals, 12 bytes away
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(12));
		//glEnableVertexAttribArray(2);
		//We like submitting texcoords on stream 2 for no special reason //The starting point of texcoords, 24 bytes away
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(24));
		// A (starting point), How many datas, normalized?, size of whole element (0=packed data), position in data ??
	//	glBindBuffer( GL_ARRAY_BUFFER , buffer_id );
		glEnableVertexAttribArray( m_attribute_id );
		// GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer
		glVertexAttribPointer( m_attribute_id , data_size , data_type , GL_FALSE , stride , NULL );
		//glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
		//glEnableVertexAttribArray(VETEX_POS_INDX);
		//glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
	}

	void Attribute::setPointer(int size, GLenum type, void *ptr)
	{
		GL_TEST_ERROR("begin")
		// glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		glVertexAttribPointer( 0 , size, type, GL_FALSE , 0 , ptr );
		GL_TEST_ERROR("end")
	}
*/

} // namespace graphics
} // namespace orion

