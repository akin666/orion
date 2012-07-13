/*
 * tproperty.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef TPROPERTY_HPP_
#define TPROPERTY_HPP_

#include "property.hpp"
#include <allocator>

namespace orion {

template <class PType>
class TProperty : public Property
{
public:
	typedef std::map< EntityID , PType* > Map;
protected:
	Map data;

	virtual void attachEntity( EntityID id )
	{
		typename Map::iterator iter = data.find( id );
		if( iter != data.end() )
		{
			return;
		}

		PType *n = Global<Allocator>::get()->create<PType>();
		data[ id ] = n;
	}

	virtual void detachEntity( EntityID id )
	{
		typename Map::iterator iter = data.find( id );
		if( iter == data.end() )
		{
			return;
		}

		PType *n = iter->second;
		data.erase( iter );
		Global<Allocator>::get()->destroy( n );
	}
public:
	TProperty()
	{
	}

	virtual ~TProperty()
	{
		// detach all!
	}

	virtual bool has( EntityID id )
	{
		return data.find( id ) != data.end();
	}

	PType& get( EntityID id )
	{
		typename Map::iterator iter = data.find( id );
		if( iter != data.end() )
		{
			return *(iter->second);
		}

		PType *n = Global<Allocator>::get()->create<PType>();
		data[ id ] = n;
		return *n;
	}

	// direct access..
	Map& access()
	{
		return data;
	}

	// Specialize
	virtual string8 getName()
	{
		return "";
	}

	// Specialize
	virtual bool parse( EntityID id , rapidxml::xml_node<> *node )
	{
		return false;
	}
};

} // namespace orion
#endif // TPROPERTY_HPP_