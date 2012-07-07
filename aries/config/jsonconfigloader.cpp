/*
 * JSONConfigLoader.cpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#include "jsonconfigloader.hpp"

#include <JsonBox.h>

#ifndef DEFAULT_CONFIG_PATH
# define DEFAULT_CONFIG_PATH "config.json"
#endif

namespace orion
{

JSONConfigLoader::JSONConfigLoader()
{
}

JSONConfigLoader::~JSONConfigLoader()
{
}

void parseValue( std::string path , JsonBox::Value& value , Config& container )
{
	// No objects here..
}

void parseObject( std::string path , const JsonBox::Value& value , Config& container )
{
	if( value.isObject() )
	{
		// Parse as object.
		const JsonBox::Object& object = value.getObject();

		std::string realPath = path;
		if( realPath != "" )
		{
			realPath += ".";
		}

		for( std::map<std::string, JsonBox::Value>::const_iterator iter = object.begin() ; iter != object.end() ; ++iter )
		{
			parseObject( realPath + iter->first , iter->second , container );
		}
	}

	// Already have full path for this thing
	// Value parsing logic..
	switch( value.getType() )
	{
		case JsonBox::Type::STRING :
		{
			container.set<std::string>( path , value.getString() );
			break;
		}
		case JsonBox::Type::INTEGER :
		{
			container.set<int32>( path , value.getInt() );
			break;
		}
		case JsonBox::Type::DOUBLE :
		{
			container.set<float64>( path , value.getDouble() );
			break;
		}
		case JsonBox::Type::OBJECT :
		{
			break;
		}
		case JsonBox::Type::ARRAY :
		{
			break;
		}
		case JsonBox::Type::BOOLEAN :
		{
			container.set<bool>( path , value.getBoolean() );
			break;
		}
		case JsonBox::Type::NULL_VALUE :
		{
			container.set<int32>( path , 0 );
			break;
		}
		case JsonBox::Type::UNKNOWN :
		{
			break;
		}
		default :
		{
			break;
		}
	}
}

bool JSONConfigLoader::load( Config& container )
{
	JsonBox::Value value;
	std::string file( DEFAULT_CONFIG_PATH );
	value.loadFromFile( file );

	// Parse data to config container!
	if( value.isObject() )
	{
		parseObject( "" , value , container );
	}

	return true;
}

} // namespace orion
