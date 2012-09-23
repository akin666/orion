/*
 * mbufmemory.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#ifndef MBUFMEMORY_HPP_
#define MBUFMEMORY_HPP_

#include "mbufbuffer.hpp"

namespace mbuf
{

class Memory : public Buffer
{
protected:
	typedef unsigned char ByteType;
	std::size_t count;
	std::size_t alignment;
	ByteType *array;
	ByteType *begin;
public:
	Memory( std::size_t size = 0 , std::size_t alignment = 0 );
	virtual ~Memory();

	Memory& setSize( std::size_t filesize );
	Memory& setAlignment( std::size_t alignment );

	void initialize();

	virtual std::size_t size() const;

	virtual void *retain( std::size_t position , std::size_t count );
	virtual void release( void *buffer );

	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace mbuf
#endif // MBUFMEMORY_HPP_ /
