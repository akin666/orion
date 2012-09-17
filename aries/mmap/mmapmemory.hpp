/*
 * mmapmemory.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#ifndef MMAPMEMORY_HPP_
#define MMAPMEMORY_HPP_

#include "mmapbuffer.hpp"

namespace mmap
{

class Memory : public Buffer
{
protected:
	typedef unsigned char ByteType;
	Size count;
	ByteType *array;
public:
	Memory( Size size );
	virtual ~Memory();

	virtual Size size() const;
	virtual void *at( Size position ) const;
	virtual void close();
	virtual bool ok();
};

} // namespace mmap
#endif // MMAPMEMORY_HPP_ /
