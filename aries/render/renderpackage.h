/*
 * renderpackage.h
 *
 *  Created on: 16.9.2012
 *      Author: akin
 */

#ifndef RENDERPACKAGE_H_
#define RENDERPACKAGE_H_

namespace render
{

class Package
{
public:
	virtual ~Package()
	{
	}

	virtual void render() = 0;
};

} // namespace render
#endif // RENDERPACKAGE_H_
