/*
 * mmapbuffer.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 *
 *      mmap::Buffer::Iterator iter = dictionary.get("HammerTime.txt").accessBuffer().begin();
 *      MyDataStructure& data = iter.read<MyDataStructure>();
 */

#ifndef MBUFMAP_HPP_
#define MBUFMAP_HPP_

#include <cstdint>

namespace mbuf {

class Buffer
{
public:
	class Iterator
	{
	private:
		const Buffer& buffer;
		std::size_t iter;
	public:
		Iterator( const Iterator& other );
		Iterator( const Buffer& buffer , std::size_t at );

		std::size_t position() const;
		std::size_t remaining() const;
		void jump( std::size_t size );
		void seek( std::size_t at );
		void *peek() const;

		template <class CType> CType *data() const
		{
			return (CType*)buffer.at( iter );
		}

		template <class CType> CType *data( std::size_t at ) const
		{
			return (CType*)buffer.at( at );
		}

		template <class CType> CType& access( std::size_t at )
		{
			return *((CType*)buffer.at( at ));
		}

		template <class CType> CType& read()
		{
			std::size_t it = iter;
			iter += sizeof( CType );
			return *((CType*)buffer.at( it ));
		}
	};
public:
	virtual ~Buffer()
	{
	}

	virtual std::size_t size() const = 0;
	virtual void *at( std::size_t position ) const = 0;
	virtual void close() = 0;
	virtual bool ok() = 0;

	Iterator begin() const;
	Iterator end() const;
};

} // namespace mbuf
#endif // MBUFMAP_HPP_
