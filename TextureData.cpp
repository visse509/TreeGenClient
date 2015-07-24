#include "stdafx.h"
#include "TextureData.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#ifndef cimg_debug
//#define cimg_debug 1
//#endif
//#include "CImg.h"
//using namespace cimg_library;
//#undef min
//#undef max
#include "SDL_image.h"
#pragma unmanaged

TextureData::TextureData(string textureName)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures( 1, &textureId );
	glBindTexture( GL_TEXTURE_2D, textureId );

	SDL_Surface *image = IMG_Load ( textureName.c_str() );
	 
	int mode = GL_RGB;
	
	if(image->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void TextureData::draw(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureId );
}

void TextureData::extrude(){

}

void TextureData::clearTexture(){
	glDeleteTextures(1,&textureId);
}

TextureData::~TextureData(void)
{
}
