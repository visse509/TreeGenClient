#include "stdafx.h"
#include "RenderObject.h"
#pragma managed

RenderObject::RenderObject(meshData *_m,TextureData *_t)
{
	m = _m;
	t = _t;
//	initShader();
}

void RenderObject::draw(){
	glEnableClientState( GL_VERTEX_ARRAY );                // Enable Vertex Arrays
    glEnableClientState( GL_TEXTURE_COORD_ARRAY ); 
	GLenum err = glGetError();
	while(err != GL_NO_ERROR){
		err = glGetError();
	}
	t->draw();
	m->draw();

	glDisableClientState( GL_VERTEX_ARRAY );                // Disable Vertex Arrays
	glDisableClientState( GL_TEXTURE_COORD_ARRAY ); 
}

void RenderObject::initShader(){
	FileReader *fragShader = new FileReader(std::string("testshader.frag"));
	FileReader *vertShader = new FileReader(std::string("testshader.vert"));
	GLuint vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vs = vertShader->text.c_str();
	const char* fs = fragShader->text.c_str();
	glShaderSourceARB(vertexShader, 1, &vs, &vertShader->size);
	glShaderSourceARB(fragmentShader, 1, &fs, &fragShader->size);

	glCompileShaderARB(vertexShader);
	glCompileShaderARB(fragmentShader);

	GLint compiled;

	glGetObjectParameterivARB(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{

	}
	glGetObjectParameterivARB(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{

	} 

	GLuint ProgramObject = glCreateProgram();

	glAttachShader(ProgramObject, vertexShader);
	glAttachShader(ProgramObject, fragmentShader);
	glLinkProgram(ProgramObject);   

	glUseProgram(ProgramObject);

}

meshData* RenderObject::getM(){
	return m;
}
TextureData* RenderObject::getT(){
	return t;
}

void RenderObject::setTexture(TextureData *_t){
	t = _t;
}
void RenderObject::clear(){
	m->clearVBO();
	//t->clearTexture();
}
RenderObject::~RenderObject(void)
{
}
