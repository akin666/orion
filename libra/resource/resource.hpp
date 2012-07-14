/*
 * resource.hpp
 *
 *  Created on: 1.7.2012
 *      Author: akin
 *
 *      States:
 *
 *  - loading -> buffered
 *
 *  - unbuffered,unrealized
 *    * unbuffer() -> (unbuffered,unrealized)
 *    * unrealize()-> (unbuffered,unrealized)
 *    * realize()  -> (unbuffered,unrealized)
 *  - buffered,unrealized
 *    * unbuffer() -> (unbuffered,unrealized)
 *    * unrealize()-> (buffered,unrealized)
 *    * realize()  -> (buffered,realized)
 *  - unbuffered,realized
 *    * unbuffer() -> (unbuffered,realized)
 *    * unrealize()-> (unbuffered,unrealized)
 *    * realize()  -> (unbuffered,realized)
 *  - buffered,realized
 *    * unbuffer() -> (unbuffered,realized)
 *    * unrealize()-> (buffered,unrealized)
 *    * realize()  -> (buffered,realized)
 */

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <orion>

namespace orion
{

class Resource
{
protected:
	uint32 state;

	void setLoading( bool val );
	void setRealized( bool val );
	void setBuffered( bool val );
public:
	Resource();
	virtual ~Resource();

	virtual bool realize() = 0;
	virtual void unrealize() = 0;
	virtual void unbuffer() = 0;

	bool hasRealized();
	bool hasBuffered();
	bool hasLoading();
};

} // namespace orion
#endif // RESOURCE_HPP_
