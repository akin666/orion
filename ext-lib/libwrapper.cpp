
#include "libwrapper.h"
#include "stb_image.h"

unsigned char *loadImage( std::vector<unsigned char>& data , int& width , int& height , int& channels )
{
	return stbi_load_from_memory( (stbi_uc const *)(&data[0]) , data.size(), &width, &height, &channels , channels );
}

void freeImageData( unsigned char *data )
{
	stbi_image_free( data );
}
