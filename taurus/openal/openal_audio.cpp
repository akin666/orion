/*
 * openal_audio.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include <orion>
#if defined( USE_OPENAL ) and ( defined(OS_WINDOWS) or defined(OS_LINUX) or defined(OS_MAC) )

#include <audio>

namespace orion
{

Audio::Audio()
{
}

Audio::~Audio()
{
}

const SoundMode& Audio::getMode() const
{
	return current;
}

void Audio::listModes( SoundModeSet& set )
{
}

bool Audio::apply( const SoundMode& mode )
{
	return true;
}

bool Audio::initialize()
{
	return true;
}

} // namespace orion

#endif
