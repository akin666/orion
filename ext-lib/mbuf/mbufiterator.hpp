/*
 * mbufiterator.hpp
 *
 *  Created on: 19.9.2012
 *      Author: akin
 */

#ifndef MBUFITERATOR_HPP_
#define MBUFITERATOR_HPP_

#include <cstdint>
#include <cstdio>

namespace mbuf
{
class Buffer;
class Iterator
{
private:
	Buffer& buffer;
	std::size_t iter;

	void *datas;

	void *retain( std::size_t it , std::size_t count );
public:
	Iterator( const Iterator& other );
	Iterator( Buffer& buffer , std::size_t at );
	~Iterator();

	std::size_t size() const;
	std::size_t position() const;
	std::size_t remaining() const;
	void jump( std::size_t size );
	void seek( std::size_t at );
	bool finished() const;
	void reset();
	void release();

	template <class CType> CType *data( std::size_t count )
	{
		std::size_t tmpsize = sizeof( CType ) * count;
		std::size_t tmpit = iter;
		iter += tmpsize;
		return (CType*)retain( tmpit , tmpsize );
	}

	template <class CType> CType *data( std::size_t it = 0  , std::size_t count )
	{
		std::size_t tmpsize = sizeof( CType ) * count;
		return (CType*)retain( it , tmpsize );
	}

	template <class CType> CType& read( std::size_t it )
	{
		return *((CType*)retain( it , sizeof( CType ) ));
	}

	template <class CType> CType& read()
	{
		std::size_t tmpsize = sizeof( CType );
		std::size_t it = iter;
		iter += tmpsize;
		return *((CType*)retain( it , tmpsize ));
	}
};

} // namespace mbuf
#endif // MBUFITERATOR_HPP_
