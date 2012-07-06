/*
 * audiomode.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef AUDIOMODE_HPP_
#define AUDIOMODE_HPP_

#include <orion>

namespace orion
{

class AudioMode
{
public:
	AudioMode();
	virtual ~AudioMode();
};

typedef std::vector<AudioMode> AudioModeSet;

} // namespace orion
#endif // AUDIOMODE_HPP_
