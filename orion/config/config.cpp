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

bool Config::loadFromString( const string8& data )
{
	Json::Reader reader;

	bool success = false;
	try
	{
		success = reader.parse( data , root );

		if( !success )
		{
			LOG->error("Failed to read data \n %s" , reader.getFormattedErrorMessages().c_str() );
		}
	}
	catch( ... )
	{
		success = false;
	}

	return success;
}

bool Config::loadFromStream( std::istream& input )
{
	Json::Reader reader;

	bool success = false;
	try
	{
		success = reader.parse( input , root );
	}
	catch( ... )
	{
		success = false;
	}

	return success;
}

bool Config::saveToString( string8& data , bool styled )
{
	// rule nO.1, You do not speak of CTOR abuse. ever. it is done. but never ever say anything about it.
	if( styled )
	{
		data = Json::StyledWriter().write( root );
	}
	else
	{
		data = Json::FastWriter().write( root );
	}
	return true;
}

bool Config::saveToStream( std::ostream& output)
{
	// rule nO.1, You do not speak of CTOR abuse. ever. it is done. but never ever say anything about it.
	Json::StyledStreamWriter().write( output , root );

	return true;
}

Json::Value *findPath( string8& key , Json::Value& root , StringPos begin = 0 )
{
	// Only Objects are allowed.
	if( !root.isObject() )
	{
		return NULL;
	}

	// find the point.
	StringPos end = key.find_first_of( '.' , begin );

	// Not point? we possibly at the last part
	if( end == string8::npos )
	{
		std::string realKey = key.substr( begin );

		if( !root.isMember( realKey ) )
		{
			return NULL;
		}

		return &(root[realKey]);
	}

	// found a point.. seek that from the object.
	std::string realKey = key.substr( begin , end );
	if( !root.isMember( realKey ) )
	{
		return NULL;
	}

	return findPath( key , root[realKey] , end + 1 );
}

Json::Value *Config::getValue( string8 key )
{
	// Did not find the value in changeset, so taking a look at original data.
	return findPath( key , root );
}

// Getters
template <> bool Config::getValue<float32>( string8 key , float32& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float32)value->asDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<float64>( string8 key , float64& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float64)value->asDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<string8>( string8 key , string8& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isString() )
	{
		type = value->asString();
		return true;
	}
	return false;
}

template <> bool Config::getValue<int32>( string8 key , int32& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isInt() )
	{
		type = value->asInt();
		return true;
	}
	return false;
}

template <> bool Config::getValue<uint32>( string8 key , uint32& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isUInt() )
	{
		type = value->asUInt();
		return true;
	}
	return false;
}

template <> bool Config::getValue<bool>( string8 key , bool& type )
{
	Json::Value *value = getValue( key );
	if( value != NULL && value->isBool() )
	{
		type = value->asBool();
		return true;
	}
	return false;
}


// Setters
Json::Value& makePath( string8& key , Json::Value& root , StringPos begin = 0 )
{
	// find the point.
	StringPos end = key.find_first_of( '.' , begin );

	// No point? we at the last part
	if( end == string8::npos )
	{
		return root;
	}

	return makePath( key , root[key.substr( begin , end )] , end + 1 );
}

string8 lastKey( const string8& key )
{
	StringPos pos = key.find_last_of(".");
	if( pos == string8::npos )
	{
		return key;
	}
	return key.substr( pos + 1 );
}

template <> void Config::setValue<float32>( string8 key , float32& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = (double)type;
}

template <> void Config::setValue<float64>( string8 key , float64& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = (double)type;
}

template <> void Config::setValue<string8>( string8 key , string8& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = type;
}

template <> void Config::setValue<int32>( string8 key , int32& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = (int)type;
}

template <> void Config::setValue<uint32>( string8 key , uint32& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = (unsigned int)type;
}

template <> void Config::setValue<bool>( string8 key , bool& type )
{
	Json::Value& parent = makePath( key , root );
	parent[ lastKey( key ) ] = type;
}


} // namespace orion
