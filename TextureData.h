
#pragma once
#include <gl\glew.h>
//#define NO_SDL_GLEXT
//#include "SDL_opengl.h"
#include <vector>
#include "TexCord.h"
#include "FileReader.h"

class TextureData
{
public:
	TextureData(string textureName);
	void draw(void);
	void extrude();
	void clearTexture();
	~TextureData(void);
	GLuint textureId;
private: 
	
};

