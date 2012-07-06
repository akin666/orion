/*
 * video.cpp
 *
 *  Created on: 6.7.2012
 *      Author: akin
 */

#include "video.hpp"

namespace orion
{

Video::Video()
{
}

Video::~Video()
{
}

const VideoMode& Video::getMode() const
{
	return current;
}

void Video::listModes( VideoModeSet& set )
{
}

bool Video::isCursorVisible()
{
	return false;
}

void Video::setCursorVisible( bool val )
{
}

void Video::setTitle( std::string head )
{
}

std::string Video::getTitle()
{
	return "";
}

} // namespace orion
