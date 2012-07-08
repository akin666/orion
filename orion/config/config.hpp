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
	// changesets
	typedef std::map<string8 , JsonBox::Value> ChangeSet;
	ChangeSet changes;

	void generateChangeTree( JsonBox::Value& changeTree , const ChangeSet& changes );

	// Datas
	JsonBox::Value root;
	const JsonBox::Value *getValue( string8 key );

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

	bool loadFromFile( const string8& path );
	bool loadFromString( const string8& data );
	bool loadFromStream( std::istream& input );

	bool saveToFile( const string8& path );
	bool saveToString( string8& data );
	bool saveToStream( std::ostream& output );

	// commit changeset to the jsonbox.
	void commit();

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
};


// specializations
// getters
template <> bool Config::getValue<float32>( string8 key , float32& type );
template <> bool Config::getValue<float64>( string8 key , float64& type );
template <> bool Config::getValue<string8>( string8 key , string8& type );
template <> bool Config::getValue<int32>( string8 key , int32& type );
template <> bool Config::getValue<bool>( string8 key , bool& type );
// setters
template <> void Config::setValue<float32>( string8 key , float32& type );
template <> void Config::setValue<float64>( string8 key , float64& type );
template <> void Config::setValue<string8>( string8 key , string8& type );
template <> void Config::setValue<int32>( string8 key , int32& type );
template <> void Config::setValue<bool>( string8 key , bool& type );


// CONFIG->get<float>("speed" , 123.0f );
// CONFIG->set<float>("speed" , 321.0f);
#define CONFIG createGlobal<Config>()

} // namespace orion
#endif // CONFIG_HPP_
