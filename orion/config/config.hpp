/*
 * config.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <orion>
#include <json>

namespace orion {

class Config
{
protected:
	Json::Value root;

	Json::Value *getValue( string8 key );

	// by default we do not recognize the type.
	template <class CType>
	bool getValue( string8 key , CType& type )
	{
		return false;
	}

	template <class CType>
	void setValue( string8 key , CType& type )
	{
	}
public:
	Config();
	virtual ~Config();

	bool loadFromString( const string8& data );
	bool loadFromStream( std::istream& input );

	bool saveToString( string8& data , bool styled = true );
	bool saveToStream( std::ostream& output );

	template <class CType>
	CType get( string8 key , CType def )
	{
		CType val;
		if( !getValue( key , val ) )
		{
			return def;
		}
		return val;
	}

	template <class CType>
	void set( string8 key , CType def )
	{
		setValue( key , def );
	}

	void has( string8 key );
};


// specializations
// getters
template <> bool Config::getValue<float32>( string8 key , float32& type );
template <> bool Config::getValue<float64>( string8 key , float64& type );
template <> bool Config::getValue<string8>( string8 key , string8& type );
template <> bool Config::getValue<int32>( string8 key , int32& type );
template <> bool Config::getValue<uint32>( string8 key , uint32& type );
template <> bool Config::getValue<bool>( string8 key , bool& type );
// setters
template <> void Config::setValue<float32>( string8 key , float32& type );
template <> void Config::setValue<float64>( string8 key , float64& type );
template <> void Config::setValue<string8>( string8 key , string8& type );
template <> void Config::setValue<int32>( string8 key , int32& type );
template <> void Config::setValue<uint32>( string8 key , uint32& type );
template <> void Config::setValue<bool>( string8 key , bool& type );


// CONFIG->get<float>("speed" , 123.0f );
// CONFIG->set<float>("speed" , 321.0f);
#define CONFIG createGlobal<Config>()

} // namespace orion
#endif // CONFIG_HPP_
