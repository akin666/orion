/*
 * mbufbuffer.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 *
 *      mbuf::Buffer::Iterator iter = dictionary.get("HammerTime.txt").accessBuffer().begin();
 *      MyDataStructure& data = iter.read<MyDataStructure>();
 */

#ifndef MBUFBUFFER_HPP_
#define MBUFBUFFER_HPP_

#include <cstdint>
#include <atomic>		// atomic things.

namespace mbuf {

class Iterator;
class Buffer
{
private:
	friend class Iterator;
	std::atomic<std::size_t> ref_count;
protected:
	std::size_t getIteratorCount();
public:
	enum Mode
	{
		CLOSED = 	0x000,
		READ = 		0x001,
		WRITE = 	0x002,
		READWRITE = 0x003,
		NO_CREATE = 0x004,
	};
public:
	virtual ~Buffer()
	{
	}

	virtual std::size_t size() const = 0;

	virtual void *retain( std::size_t position , std::size_t count ) = 0;
	virtual void release( void *buffer ) = 0;

	virtual bool open( Mode mode ) = 0;
	virtual void close() = 0;
	virtual bool ok() const = 0;
	virtual Mode getMode() const = 0;

	Iterator begin();
};

} // namespace mbuf
#endif // MBUFBUFFER_HPP_
