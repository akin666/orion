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

} // namespace mbuf
#endif // MBUFMEMORY_HPP_ /
