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

bool Config::loadFromFile( const string8& path )
{
	root.loadFromFile( path );
	return true;
}

bool Config::loadFromString( const string8& data )
{
	root.loadFromString( data );
	return true;
}

bool Config::loadFromStream( std::istream& input )
{
	root.loadFromStream( input );
	return true;
}


bool Config::saveToFile( const string8& path )
{
	commit();
	root.writeToFile( path );
	return true;
}

bool Config::saveToString( string8& data )
{
	commit();

	std::ostringstream stream;
	root.writeToStream( stream );
	data = stream.str();

	return true;
}

bool Config::saveToStream( std::ostream& output )
{
	commit();

	root.writeToStream( output );
	return true;
}

const JsonBox::Value *findPath( string8& key , const JsonBox::Value& root , StringPos begin = 0 )
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
	if( end == string8::npos )
	{
		std::map<string8, JsonBox::Value>::const_iterator iter = object.find( key.substr( begin ) );
		if( iter == object.end() )
		{
			return NULL;
		}

		return &(iter->second);
	}

	// found a point.. seek that from the object.
	std::map<string8, JsonBox::Value>::const_iterator iter = object.find( key.substr( begin , end ) );
	if( iter == object.end() )
	{
		return NULL;
	}

	return findPath( key , iter->second , end + 1 );
}

const JsonBox::Value *Config::getValue( string8 key )
{
	// JsonBox::Value root, has all the data.
	// key is dot splitted.

	// First take a look at changeset.
	ChangeSet::iterator iter = changes.find( key );
	if( iter != changes.end() )
	{
		return &(iter->second);
	}

	// Did not find the value in changeset, so taking a look at original data.
	return findPath( key , root );
}


class ConfigChangeNode
{
public:
	typedef std::map<string8 , ConfigChangeNode*> NodeMap;
	ConfigChangeNode()
	: value( NULL )
	{
	}

	~ConfigChangeNode()
	{
		for( NodeMap::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			delete (iter->second);
		}
		childs.clear();
		delete value;
		value = NULL;
	}

	NodeMap childs;
	JsonBox::Value *value;
};

void pushToTree( const string8& path , const JsonBox::Value& value , ConfigChangeNode& root , StringPos begin = 0 )
{
	StringPos end = path.find_first_of( '.' , begin );

	string8 name;

	if( end == string8::npos )
	{
		name = path.substr( begin );
	}
	else
	{
		name = path.substr( begin , end );
	}

	// Get or Generate node.
	ConfigChangeNode::NodeMap::iterator iter = root.childs.find( name );
	ConfigChangeNode* node = NULL;
	if( iter == root.childs.end() )
	{
		// no such child.
		node = new ConfigChangeNode;
		root.childs[name] = node;
	}
	else
	{
		// such child
		node = iter->second;
	}

	// no points. so this is the end node.
	if( end == string8::npos )
	{
		if( node != NULL )
		{
			if( node->value == NULL )
			{
				node->value = new JsonBox::Value;
			}

			*(node->value) = value;
		}
		return;
	}

	// middle node..
	pushToTree( path , value , *node , end + 1 );
}

void generateTree( JsonBox::Object& object , ConfigChangeNode& root )
{
	for( ConfigChangeNode::NodeMap::iterator iter = root.childs.begin() ; iter != root.childs.end() ; ++iter )
	{
		if( iter->second->value != NULL )
		{
			// Leaf value!
			object[ iter->first ] = *(iter->second->value);
		}
		else
		{
			// Node!
			JsonBox::Object object2;
			generateTree( object2 , *iter->second );
			object[ iter->first ] = JsonBox::Value( object2 );
		}
	}
}

void Config::generateChangeTree( JsonBox::Value& changeTree , const ChangeSet& changes )
{
	ConfigChangeNode nodeRoot;
	for( ChangeSet::const_iterator iter = changes.begin() ; iter != changes.end() ; ++iter )
	{
		pushToTree( iter->first , iter->second , nodeRoot );
	}


	JsonBox::Object object;
	// Now we have node tree.. now generate the ChangeTree..
	generateTree( object , nodeRoot );

	changeTree.setObject( object );
}

// commit changeset to the root(jsonbox).
void Config::commit()
{
	// This is pretty WTF thing..
	if( changes.size() <= 0 )
	{
		return;
	}

	JsonBox::Value changeTree;
	generateChangeTree( changeTree , changes );
	changes.clear();

	// OK, now we have 2 trees.. the original and the ChangeTree..
	// Merge them..

	// TODO!
}

// Getters
template <> bool Config::getValue<float32>( string8 key , float32& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float32)value->getDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<float64>( string8 key , float64& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isDouble() )
	{
		type = (float64)value->getDouble();
		return true;
	}
	return false;
}

template <> bool Config::getValue<string8>( string8 key , string8& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isString() )
	{
		type = value->getString();
		return true;
	}
	return false;
}

template <> bool Config::getValue<int32>( string8 key , int32& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isInteger() )
	{
		type = value->getInt();
		return true;
	}
	return false;
}

template <> bool Config::getValue<bool>( string8 key , bool& type )
{
	const JsonBox::Value *value = getValue( key );
	if( value != NULL && value->isBoolean() )
	{
		type = value->getBoolean();
		return true;
	}
	return false;
}


// Setters
template <> void Config::setValue<float32>( string8 key , float32& type )
{
	changes[ key ] = JsonBox::Value( (double)type );
}

template <> void Config::setValue<float64>( string8 key , float64& type )
{
	changes[ key ] = JsonBox::Value( (double)type );
}

template <> void Config::setValue<string8>( string8 key , string8& type )
{
	changes[ key ] = JsonBox::Value( type );
}

template <> void Config::setValue<int32>( string8 key , int32& type )
{
	changes[ key ] = JsonBox::Value( type );
}

template <> void Config::setValue<bool>( string8 key , bool& type )
{
	changes[ key ] = JsonBox::Value( type );
}


} // namespace orion
