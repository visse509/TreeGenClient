#include "stdafx.h"
#include "meshdata.h"
#include "TexCord.h"
#pragma managed
const double PI = 3.1415926;
meshData::meshData(int vertexSize, int indiceSize)
{

listSize = 0;
//index = new unsigned short[indiceSize];

}

void meshData::draw(){
	GLenum err = glGetError();
	while(err != GL_NO_ERROR){
		err = glGetError();
	}
    glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER_ARB,textureCoordId);
	glTexCoordPointer( 2, GL_FLOAT, 0, (char *) NULL );  

    glBindBuffer(GL_ARRAY_BUFFER_ARB, vertexId);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceId);

    glDrawElements(GL_TRIANGLES,n_indices, GL_UNSIGNED_SHORT,NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void meshData::addVboData(){

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);


	if(texCords.size() > 0){
		glGenBuffersARB(1, &textureCoordId);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, textureCoordId);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(float)*texCords.size(), &texCords[0], GL_DYNAMIC_DRAW_ARB);
	}

    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
	glBufferData(GL_ARRAY_BUFFER, 3 * (vertexList.size()) * sizeof(GLfloat), getData(), GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  indiceId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (n_indices) * sizeof(GLushort), &index[0], GL_DYNAMIC_DRAW_ARB);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);

}
void meshData::initMesh(){
	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
       
    }
    glGenBuffers(1, &vertexId);
    glGenBuffers(1, &indiceId);
    addVboData();
	
}

float* meshData::getData(){
    float* data;
    data = new float[listSize*3];

    for(int i = 0; i < listSize*3; i++)
        data[i] = 0.0;


    for(int i = 0; i < listSize;i++){
        data[i*3] = vertexList[i]->x;
        data[i*3+1] = vertexList[i]->y;
        data[i*3+2] = vertexList[i]->z;
    }
    return data;
}
void meshData::clearVBO(){
//	glDeleteBuffers(1, &vertexId);
//	glDeleteBuffers(1, &indiceId);
//	glDeleteBuffers(1, &textureCoordId);
}

void meshData::setNIndices(int n){
	n_indices = n;
}

int meshData::getNIndices(){
	return n_indices;
}

void meshData::setListSize(int size){
	listSize = size;
}

int meshData::getListSize(){
	return listSize;
}
void meshData::move(float x, float y, float z){
    for(int i = 0; i < listSize; i++){
        float newX = vertexList[i]->x + x;
        float newY = vertexList[i]->y + y;
        float newZ = vertexList[i]->z + z;
        vertexList[i]->Set(Vert(newX, newY, newZ));

    }
}

void meshData::moveMesh(Vert *p1, Vert *p2){
    for(int i  = 0; i < listSize;i++){
		vertexList[i]->x += (p1->x - p2->x);
        vertexList[i]->y += (p1->y - p2->y);
        vertexList[i]->z += (p1->z - p2->z);
    }
}
meshData::~meshData(){
    //for(int i = 0; i < listSize; i++){
	//	Vert *v = 
	
	//}
  // delete index;
}
