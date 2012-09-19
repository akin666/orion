/*
 * mbufiterator.hpp
 *
 *  Created on: 19.9.2012
 *      Author: akin
 */

#ifndef MBUFITERATOR_HPP_
#define MBUFITERATOR_HPP_

#include <cstdint>

namespace mbuf
{
class Buffer;
class Iterator
{
private:
	Buffer& buffer;
	std::size_t iter;

	void *at( std::size_t it ) const;
public:
	Iterator( const Iterator& other );
	Iterator( Buffer& buffer , std::size_t at );
	~Iterator();

	std::size_t position() const;
	std::size_t remaining() const;
	void jump( std::size_t size );
	void seek( std::size_t at );
	void *peek() const;
	bool finished() const;
	void reset();

	template <class CType> CType *data() const
	{
		return (CType*)at( iter );
	}

	template <class CType> CType *data( std::size_t it ) const
	{
		return (CType*)at( it * sizeof(CType) );
	}

	template <class CType> CType& access( std::size_t it )
	{
		return *((CType*)at( it * sizeof(CType) ));
	}

	template <class CType> CType *byteAccess( std::size_t it ) const
	{
		return (CType*)at( it );
	}

	template <class CType> CType& byteAccess( std::size_t it )
	{
		return *((CType*)at( it ));
	}

	template <class CType> CType& read()
	{
		std::size_t it = iter;
		iter += sizeof( CType );
		return *((CType*)at( it ));
	}
};

} // namespace mbuf
#endif // MBUFITERATOR_HPP_
