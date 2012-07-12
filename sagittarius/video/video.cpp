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

const graphics::RenderTargetSetting& Video::getMode() const
{
	return current;
}

void Video::listModes( graphics::RenderTargetSettingSet& set )
{
}

bool Video::isCursorVisible()
{
	return false;
}

void Video::setCursorVisible( bool val )
{
}

void Video::setTitle( string8 head )
{
}

string8 Video::getTitle()
{
	return "";
}

} // namespace orion
