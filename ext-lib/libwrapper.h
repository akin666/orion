
#ifndef LIB_WRAPPER_H_
#define LIB_WRAPPER_H_

#include <vector>

unsigned char *loadImage( std::vector<unsigned char>& data , int& width , int& height , int& channels );
void freeImageData( unsigned char *data );

#endif // LIB_WRAPPER_H_

