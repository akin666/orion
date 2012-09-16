/*
 * renderipackage.h
 *
 *  Created on: 16.9.2012
 *      Author: akin
 */

#ifndef RENDERIPACKAGE_H_
#define RENDERIPACKAGE_H_

namespace render
{

class IPackage
{
public:
	virtual ~IPackage()
	{
	}

	virtual void render() = 0;
};

} // namespace render
#endif // RENDERIPACKAGE_H_
