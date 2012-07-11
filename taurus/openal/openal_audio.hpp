/*
 * openal_audio.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef OPENAL_AUDIO_HPP_
#define OPENAL_AUDIO_HPP_

#include <audio/audio.hpp>

namespace orion
{

class OpenALAudio : public Audio
{
public:
	OpenALAudio();
	virtual ~OpenALAudio();

	virtual void listModes( AudioModeSet& set );

	virtual bool apply( AudioMode& mode );
	virtual bool initialize();
};

} // namespace orion
#endif // OPENAL_AUDIO_HPP_
