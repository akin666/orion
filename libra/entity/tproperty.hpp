/*
 * tproperty.hpp
 *
 *  Created on: 16.6.2012
 *      Author: akin
 */

#ifndef TPROPERTY_HPP_
#define TPROPERTY_HPP_

#include "property.hpp"
#include <pool>

namespace orion {

template <class PType>
class TProperty : public Property
{
public:
	Pool<PType> pool;
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

		PType *n = pool.create();
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
		pool.release( n );
	}

	virtual void enableEntity( bool enabled , EntityID id )
	{
		typename Map::iterator iter = data.find( id );
		if( iter == data.end() )
		{
			return;
		}

		PType *n = iter->second;
		n->enable( enabled );
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

		PType *n = pool.create();
		data[ id ] = n;
		return *n;
	}

	PType *getNoCreate( EntityID id )
	{
		typename Map::iterator iter = data.find( id );
		if( iter != data.end() )
		{
			return (iter->second);
		}

		return NULL;
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
	virtual bool parse( EntityID id , Json::Value& node )
	{
		return false;
	}
};

} // namespace orion
#endif // TPROPERTY_HPP_
