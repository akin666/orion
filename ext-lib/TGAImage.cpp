
#include "TGAImage.h"
#include <string>
#include <fstream>
#include <iostream>

namespace imagesaver {

bool writeImageRGBA8( std::string filename , int width , int height , void *pixels )
{
	//Error checking
	if( pixels == NULL || width <= 0 || height <= 0 )
	{
		std::cout << "Image size is not set properly" << std::endl;
		return false;
	}

	std::ofstream o(filename.c_str(), std::ios::out | std::ios::binary);

	//Write the header
	o.put(0);
   	o.put(0);
   	o.put(2);                         // uncompressed RGB
   	o.put(0); 	o.put(0);
   	o.put(0); 	o.put(0);
   	o.put(0);
   	o.put(0); 	o.put(0);           // X origin
   	o.put(0); 	o.put(0);           // y origin
   	o.put((width & 0x00FF));
   	o.put((width & 0xFF00) / 256);
   	o.put((height & 0x00FF));
   	o.put((height & 0xFF00) / 256);
   	o.put(32);                        // 24 bit bitmap
   	o.put(0);
   	
	//Write the pixel data
   	int max = height * width * 4;
	for( int i = 0 ; i < max ;i += 4 )
	{
		o.put( ((char*)pixels)[i+2] );
		o.put( ((char*)pixels)[i+1] );
		o.put( ((char*)pixels)[i+0] );
		o.put( ((char*)pixels)[i+3] );
	}   
	
	//close the file
	o.close();

	return true;
}

} // imagesaver

