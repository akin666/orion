/*
 * config.hpp
 *
 *  Created on: 17.6.2012
 *      Author: akin
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <orion>
#include <stringtools>

namespace orion {

class Config
{
protected:
	typedef std::string::size_type StrPos;

	class Node
	{
	protected:
		typedef std::map<std::string , Node> ChildSet;
		ChildSet childs;
		std::string value;
	public:
		Node();
		Node( const Node& o );

		std::string *get( const std::string& key , StrPos begin = 0 );
		void set( const std::string& key , const std::string& val , StrPos begin = 0 );
	};

	Node root;

	std::string *getString( const std::string& key );
	void setString( const std::string& key , const std::string& val );
public:
	Config();
	virtual ~Config();

	bool has( std::string key );

	template <class CType>
	void set( std::string key , CType val )
	{
		setString( key , stringtools::to_ot<std::string , CType >( val ) );
	}

	template <class CType>
	CType get( std::string key )
	{
		std::string *ptr = getString( key );
		if( ptr == NULL )
		{
			CType tt;
			return tt;
		}
		return stringtools::to_ot<CType , std::string>( *ptr );
	}

	template <class CType>
	CType get( std::string key , CType def )
	{
		std::string *ptr = getString( key );
		if( ptr == NULL )
		{
			set( key , def );
			return def;
		}
		return stringtools::to_ot<CType , std::string>( *ptr );
	}
};

// CONFIG->get<float>("speed");
// CONFIG->get<float>("speed" , 123.0f );
// CONFIG->set<float>("speed" , 321.0f);
#define CONFIG createGlobal<Config>()

} // namespace orion
#endif // CONFIG_HPP_
