/*
 * config.cpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#include "config.hpp"

namespace orion {

Config::Config()
{
}

Config::~Config()
{
}

bool Config::loadFromFile( std::string path )
{
	root.loadFromFile( path );
	return true;
}

bool Config::loadFromString( std::string data )
{
	root.loadFromString( data );
	return true;
}

const JsonBox::Value *findPath( std::string& key , const JsonBox::Value& root , StringPos begin = 0 )
{
	// Only Objects are allowed.
	if( !root.isObject() )
	{
		return NULL;
	}
	const JsonBox::Object& object = root.getObject();

	// find the point.
	StringPos end = key.find_first_of( '.' , begin );

	// Not point? we possibly at the last part
	if( end == std::string::npos )
	{
		std::map<std::string, JsonBox::Value>::const_iterator iter = object.find( key.substr( begin ) );
		if( iter == object.end() )
		{
			return NULL;
		}

		return &(iter->second);
	}

	// found a point.. seek that from the object.
	std::map<std::string, JsonBox::Value>::const_iterator iter = object.find( key.substr( begin , end ) );
	if( iter == object.end() )
	{
		return NULL;
	}

	return findPath( key , iter->second , end + 1 );
}

const JsonBox::Value *Config::getValue( std::string key )
{
	// JsonBox::Value root, has all the data.
	// key is dot splitted.

	return findPath( key , root );
}

template <> bool Config::getValue<float32>( std::string key , float32& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float32)value->getDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<float64>( std::string key , float64& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float64)value->getDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<std::string>( std::string key , std::string& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isString() )
	{
		type = value->getString();
		return true;
	}
	return false;
}

template <> bool Config::getValue<int32>( std::string key , int32& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isInteger() )
	{
		type = value->getInt();
		return true;
	}
	return false;
}

template <> bool Config::getValue<bool>( std::string key , bool& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isBoolean() )
	{
		type = value->getBoolean();
		return true;
	}
	return false;
}



} // namespace orion
