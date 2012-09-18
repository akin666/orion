/*
 * graphicsbuffer.hpp
 *
 *  Created on: 13.7.2012
 *      Author: akin
 */

#ifndef GRAPHICSBUFFER_HPP_
#define GRAPHICSBUFFER_HPP_

#include "mbufbuffer.hpp"

namespace orion {
namespace graphics {

class Buffer : public mbuf::Buffer
{
public:
	enum Residence
	{
		GPU = 0x001,
		CPU = 0x002,
		CPUGPU = 0x003
	};
	enum Interval
	{
		ONCE = 0x001,
		OCCASIONALLY = 0x002,
		MULTI = 0x004
	};
private:
	unsigned int id;
	std::size_t bsize;
	Mode mode;
public:
	Buffer();
	virtual ~Buffer();

	void initialize( std::size_t size , Residence residence , Interval interval );

	virtual std::size_t size() const;
	virtual void *at( std::size_t position ) const;
	virtual bool open( Mode mode );
	virtual void close();
	virtual bool ok() const;
	virtual Mode getMode() const;
};

} // namespace graphics 
} // namespace orion 
#endif // GRAPHICSBUFFER_HPP_ 
