/*
 * graphicsbuffer.hpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSBUFFER_HPP_
#define GRAPHICSBUFFER_HPP_

#include <mbuf/mbufbuffer.hpp>

namespace orion {
namespace graphics {

class Buffer : public mbuf::Buffer
{
private:
	unsigned int id;
	std::size_t bsize;
	Mode mode;
	void *ptr;
public:
	Buffer();
	virtual ~Buffer();

	void initialize( unsigned int id );

	virtual std::size_t size() const;

	virtual void *retain( std::size_t position , std::size_t count );
	virtual void release( void *buffer );

	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace graphics 
} // namespace orion 
#endif // GRAPHICSBUFFER_HPP_ 
