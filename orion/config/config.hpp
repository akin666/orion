/*
 * config.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <orion>
#include <JsonBox.h>

namespace orion {

class Config
{
protected:
	typedef std::map<std::string , JsonBox::Value> ChangeSet;

	JsonBox::Value root;
	ChangeSet changes;

	const JsonBox::Value *getValue( std::string key );

	// by default we do not recognize the type.
	template <class CType>
	bool getValue( std::string key , CType& type )
	{
		return false;
	}

	template <class CType>
	void setValue( std::string key , CType& type )
	{
	}
public:
	Config();
	virtual ~Config();

	bool loadFromFile( const std::string& path );
	bool loadFromString( const std::string& data );
	bool loadFromStream( std::istream& input );

	bool saveToFile( const std::string& path );
	bool saveToString( std::string& data );
	bool saveToStream( std::ostream& output );

	// commit changeset to the jsonbox.
	void commit();

	template <class CType>
	CType get( std::string key , CType def )
	{
		CType val;
		if( !getValue( key , val ) )
		{
			return def;
		}
		return val;
	}

	template <class CType>
	void set( std::string key , CType def )
	{
		setValue( key , def );
	}
};


// specializations
// getters
template <> bool Config::getValue<float32>( std::string key , float32& type );
template <> bool Config::getValue<float64>( std::string key , float64& type );
template <> bool Config::getValue<std::string>( std::string key , std::string& type );
template <> bool Config::getValue<int32>( std::string key , int32& type );
template <> bool Config::getValue<bool>( std::string key , bool& type );
// setters
template <> void Config::setValue<float32>( std::string key , float32& type );
template <> void Config::setValue<float64>( std::string key , float64& type );
template <> void Config::setValue<std::string>( std::string key , std::string& type );
template <> void Config::setValue<int32>( std::string key , int32& type );
template <> void Config::setValue<bool>( std::string key , bool& type );


// CONFIG->get<float>("speed" , 123.0f );
// CONFIG->set<float>("speed" , 321.0f);
#define CONFIG createGlobal<Config>()

} // namespace orion
#endif // CONFIG_HPP_
