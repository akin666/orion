/*
 * indextool.hpp
 *
 *  Created on: Sep 7, 2012
 *      Author: akin
 */

#ifndef INDEXTOOL_HPP_
#define INDEXTOOL_HPP_

#include <orion>
#include <cstring>

namespace orion
{

class IndexTool
{
protected:
	typedef string8 CType;
	typedef std::map< CType , uint > KeyIndex;
	typedef std::map< uint , CType > IndexKey;
	uint at;
	KeyIndex keyIndex;
	IndexKey indexKey;
public:
	IndexTool()
	: at(0)
	{
	}

	uint get( const string8& key )
	{
		KeyIndex::iterator iter = keyIndex.find( key );
		if( iter == keyIndex.end() )
		{
			keyIndex[ key ] = at;
			indexKey[ at ] = key;

			return at++;
		}
		return iter->second;
	}
};

} // namespace orion

#endif /* INDEXTOOL_HPP_ */
