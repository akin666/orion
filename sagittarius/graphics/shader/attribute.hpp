/*
 * attribute.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <orion>

namespace orion {
namespace graphics {

	class Attribute
	{
	protected:
		uint m_program_id;
		int m_attribute_id;
		std::string m_name;
	public:
		Attribute();
		virtual ~Attribute();

		void setProgram( uint program );
		void attach( std::string name ) throw (std::exception);
		std::string getName();

		void setPointer( int size , GLenum type , void *ptr ) throw (std::exception);
		void setPointer( int data_size , GLenum data_type , GLsizei stride ) throw (std::exception);

		void enable() throw (std::exception);
		void disable() throw (std::exception);

		void set( float v ) throw (std::exception);
		void set( float v , float v2 ) throw (std::exception);
		void set( float v , float v2 , float v3 ) throw (std::exception);
		void set( float v , float v2 , float v3 , float v4 ) throw (std::exception);
		void set( double v ) throw (std::exception);
		void set( double v , double v2 ) throw (std::exception);
		void set( double v , double v2 , double v3 ) throw (std::exception);
		void set( double v , double v2 , double v3 , double v4 ) throw (std::exception);
		void set( short v ) throw (std::exception);
		void set( short v , short v2 ) throw (std::exception);
		void set( short v , short v2 , short v3 ) throw (std::exception);
		void set( short v , short v2 , short v3 , short v4 ) throw (std::exception);

		void set( float *v ) throw (std::exception);
		void set2( float *v ) throw (std::exception);
		void set3( float *v ) throw (std::exception);
		void set4( float *v ) throw (std::exception);

		void set( double *v ) throw (std::exception);
		void set2( double *v ) throw (std::exception);
		void set3( double *v ) throw (std::exception);
		void set4( double *v ) throw (std::exception);

		void set( short *v ) throw (std::exception);
		void set2( short *v ) throw (std::exception);
		void set3( short *v ) throw (std::exception);
		void set4( short *v ) throw (std::exception);

		void set4( int *v ) throw (std::exception);
		void set4( char *v ) throw (std::exception);
		void set4( unsigned char *v ) throw (std::exception);
		void set4( unsigned short *v ) throw (std::exception);
		void set4( uint *v ) throw (std::exception);

		// normalized
		void setN( unsigned char v , unsigned char v2 , unsigned char v3 , unsigned char v4 ) throw (std::exception);
		void set4N( char *v ) throw (std::exception);
		void set4N( short *v ) throw (std::exception);
		void set4N( int *v ) throw (std::exception);
		void set4N( unsigned char *v ) throw (std::exception);
		void set4N( unsigned short *v ) throw (std::exception);
		void set4N( uint *v ) throw (std::exception);
	};

} // namespace graphics
} // namespace orion

#endif /* ATTRIBUTE_H_ */
