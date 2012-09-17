/*
 * mmapbuffer.hpp
 *
 *  Created on: 17.9.2012
 *      Author: akin
 *
 *      mmap::Buffer::Iterator iter = dictionary.get("HammerTime.txt").accessBuffer().begin();
 *      MyDataStructure& data = iter.read<MyDataStructure>();
 */

#ifndef MMAPMAP_HPP_
#define MMAPMAP_HPP_

namespace mmap
{

class Buffer
{
public:
	typedef int Size;

	class Iterator
	{
	private:
		Buffer& buffer;
		Size iter;
	public:
		Iterator( const Iterator& other );
		Iterator( Buffer& buffer , Size& at = 0 );

		Size position() const;
		Size remaining() const;
		void jump( Size size );
		void seek( Size at );
		void *peek() const;
		void *end() const;

		template <class CType> CType *data() const
		{
			return (CType*)buffer.at( iter );
		}

		template <class CType> CType *data( Size at ) const
		{
			return (CType*)buffer.at( at );
		}

		template <class CType> CType& access( Size at )
		{
			return *((CType*)buffer.at( at ));
		}

		template <class CType> CType& read()
		{
			Size it = iter;
			iter += sizeof( CType );
			return *((CType*)buffer.at( it ));
		}
	};
public:
	virtual ~Buffer()
	{
	}

	virtual Size size() const = 0;
	virtual void *at( Size position ) const = 0;
	virtual void close() = 0;
	virtual bool ok() = 0;

	Iterator begin() const;
	Iterator end() const;
};

} // namespace mmap
#endif // MMAPBUFFER_HPP_
