/*
 * audio.hpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <orion>
#include "audiomode.hpp"

namespace orion
{

class Audio
{
protected:
	AudioMode current;
public:
	Audio();
	virtual ~Audio();

	const AudioMode& getMode() const;

	virtual void listModes( AudioModeSet& set );

	virtual bool apply( AudioMode& mode ) = 0;
	virtual bool initialize() = 0;
};

} // namespace orion
#endif // AUDIO_HPP_
