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
	JsonBox::Value root;

	const JsonBox::Value *getValue( std::string key );

	// by default we do not recognize the type.
	template <class CType>
	bool getValue( std::string key , CType& type )
	{
		return false;
	}
public:
	Config();
	virtual ~Config();

	bool loadFromFile( std::string path );
	bool loadFromString( std::string data );

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
};


// specializations
template <> bool Config::getValue<float32>( std::string key , float32& type );
template <> bool Config::getValue<float64>( std::string key , float64& type );
template <> bool Config::getValue<std::string>( std::string key , std::string& type );
template <> bool Config::getValue<int32>( std::string key , int32& type );
template <> bool Config::getValue<bool>( std::string key , bool& type );

// CONFIG->get<float>("speed");
// CONFIG->get<float>("speed" , 123.0f );
// CONFIG->set<float>("speed" , 321.0f);
#define CONFIG createGlobal<Config>()

} // namespace orion
#endif // CONFIG_HPP_
