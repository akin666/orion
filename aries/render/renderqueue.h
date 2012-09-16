/*
 * RENDERQUEUE_H_
 *
 *  Created on: 16.9.2012
 *      Author: akin
 */

#ifndef RENDERQUEUE_H_
#define RENDERQUEUE_H_

#include <queue>
#include <iostream>
#include <uthread>

#include "renderipackage.h"

namespace render
{

template <class CType = IPackage>
class Queue
{
protected:
	std::mutex mutex;
	std::queue<CType*> que;
public:
	void push( CType *data )
	{
		std::lock_guard<std::mutex> lock(mutex);
		que.push_back( data );
	}

	CType *pop()
	{
		std::lock_guard<std::mutex> lock(mutex);

		CType *popped = NULL;
		if( !data.empty() )
		{
			popped = que.front();
			que.pop_front();
		}
		return popped;
	}
};

} // namespace render
#endif // RENDERQUEUE_H_
