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

	void load( std::string path );
};

} // namespace orion 
#endif // IQMLOADER_HPP_ 
