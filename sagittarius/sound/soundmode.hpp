/*
 * SoundMode.hpp
 *
 *  Created on: 7.7.2012
 *      Author: akin
 */

#ifndef SOUNDMODE_HPP_
#define SOUNDMODE_HPP_

#include <orion>

namespace orion
{

class SoundMode
{
public:
	SoundMode();
	virtual ~SoundMode();
};

typedef std::vector<SoundMode> SoundModeSet;

} // namespace orion
#endif // SOUNDMODE_HPP_
