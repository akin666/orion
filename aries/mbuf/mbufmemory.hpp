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
	ByteType *array;
public:
	Memory( std::size_t size = 0 );
	virtual ~Memory();

	Memory& setSize( std::size_t filesize );
	void initialize();

	virtual std::size_t size() const;
	virtual void *at( std::size_t position ) const;
	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace mbuf
#endif // MBUFMEMORY_HPP_ /
