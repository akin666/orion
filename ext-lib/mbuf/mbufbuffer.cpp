/*
 * mbufbuffer.cpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 */

#include "mbufbuffer.hpp"
#include "mbufiterator.hpp"

namespace mbuf {

std::size_t Buffer::getIteratorCount()
{
	return ref_count;
}

Iterator Buffer::begin()
{
	return Iterator( *this , 0 );
}

} // namespace mbuf

