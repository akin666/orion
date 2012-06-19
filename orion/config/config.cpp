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


Config::Node::Node()
{
}

Config::Node::Node( const Node& o )
: childs( o.childs ),
  value( o.value )
{
}

std::string *Config::Node::get( const std::string& key , StrPos begin )
{
//	typedef std::map<std::string , Node> ChildSet;
//	ChildSet childs;
//	std::string value;
	// find first '.'
	StrPos pos = key.find_first_of( '.' , begin );

	// dot no found?!
	if( pos == std::string::npos )
	{
		ChildSet::iterator iter = childs.find( key.substr( begin ) );

		if( iter != childs.end() )
		{
			return &(iter->second.value);
		}

		return NULL;
	}

	ChildSet::iterator iter = childs.find( key.substr( begin , pos - 1 ) );

	if( iter != childs.end() )
	{
		return iter->second.get( key , pos + 1 );
	}

	return NULL;
}

void Config::Node::set( const std::string& key , const std::string& val , StrPos begin )
{
}

std::string *Config::getString( const std::string& key )
{
	// Strip the path, and seek.. from root..
	return root.get( key );
}

void Config::setString( const std::string& key , const std::string& val )
{
	return root.set( key , val );
}

bool Config::has( std::string key )
{
	return getString( key ) != NULL;
}


} // namespace orion
