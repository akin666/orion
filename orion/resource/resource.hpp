/*
 * resource.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 */

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

namespace orion
{

class Resource
{
protected:
	enum State
	{
		None = 		0x0000,
		Buffered = 	0x0001,
		Loaded = 	0x0002,
		BufferedLoaded = Buffered + Loaded
	};
	State state;

	void setLoaded( bool val );
	void setBuffered( bool val );
public:
	Resource();
	virtual ~Resource();

	virtual bool load() = 0;
	virtual void unload() = 0;

	bool loaded();
	bool buffered();
};

} // namespace orion
#endif // RESOURCE_HPP_
