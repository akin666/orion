/*
 *  main.cpp
 *  ImageSaver
 *
 *  Created by Daniel Beard on 6/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 *
 * The library was heavily modified, to be just a single C function.
*/

#ifndef __TGAIMAGE_SAVER__
#define __TGAIMAGE_SAVER__

//includes
#include <string>

namespace imagesaver {

bool RGBA8write( std::string filename , int width , int height , void *pixels );
bool RGB8write( std::string filename , int width , int height , void *pixels );
bool ALPHA8write( std::string filename , int width , int height , void *pixels );

} // imagesaver

#endif // __TGAIMAGE_SAVER__
