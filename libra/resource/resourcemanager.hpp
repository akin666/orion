/*
 * resourcemanager.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <orion>

namespace orion
{

template <class ResType>
class ResourceManager
{
public:
	ResourceManager()
	{
		// Pesky autoregistering to global!
		Global<ResourceManager<ResType> >::set( this );
	}

	virtual ~ResourceManager()
	{
	}

	virtual bool has( const string8& ident ) = 0;
	virtual void load( const string8& ident , const string8& path ) = 0;
	virtual void unload( const string8& ident ) = 0;
	virtual ResType& get( const string8& ident ) = 0;

	// Realize all resourcemanagers resources
	virtual void realize() = 0;
	// Unrealize all resourcemanagers resources
	virtual void unrealize() = 0;
	// Unbuffer all resourcemanagers resources
	virtual void unbuffer() = 0;
};

// using..
// GlobalTeck
// Sugar Coating
template <class CType>
void loadResource( const string8& ident , const string8& path )
{
	Global<ResourceManager<CType> >::get()->load( ident , path );
}

template <class CType>
CType& getResource( const string8& ident )
{
	Global<ResourceManager<CType> >::get()->get( ident );
}

template <class CType>
bool hasResource( const string8& ident )
{
	return Global<ResourceManager<CType> >::get()->has( ident );
}

template <class CType>
void realizeResource()
{
	Global<ResourceManager<CType> >::get()->realize();
}

template <class CType>
void unrealizeResource()
{
	Global<ResourceManager<CType> >::get()->unrealize();
}

template <class CType>
void unbufferResource()
{
	Global<ResourceManager<CType> >::get()->unbuffer();
}

} // namespace orion
#endif // RESOURCEMANAGER_HPP_
