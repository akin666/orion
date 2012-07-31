/*
 * iqmloader.hpp
 *
 *  Created on: 26.7.2012
 *      Author: akin
 */

#ifndef IQMLOADER_HPP_
#define IQMLOADER_HPP_

#include <orion>

namespace orion
{

class IQMLoader
{
public:
	IQMLoader();
	virtual ~IQMLoader();

	bool load( const std::string& path );
	bool load( const uint8 *buffer , uint32 maxlen );
};

} // namespace orion 
#endif // IQMLOADER_HPP_ 
