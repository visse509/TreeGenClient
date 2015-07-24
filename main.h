/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//The headers
#include <gl\glew.h>
#include "SDL.h"
#define NO_SDL_GLEXT
#include "SDL_opengl.h"

//Screen attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//Event handler
SDL_Event event;

//Rendering flag
bool renderQuad = true;
bool m_mouseClick = false;
