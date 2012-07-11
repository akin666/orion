/*
 * audio.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "audio.hpp"

namespace orion
{

Audio::Audio()
{
}

Audio::~Audio()
{
}

const AudioMode& Audio::getMode() const
{
	return current;
}

void Audio::listModes( AudioModeSet& set )
{
}

} // namespace orion
