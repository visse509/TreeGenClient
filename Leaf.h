#pragma once
#include "meshdata.h"
#include "RenderObject.h"
#include "TextureData.h"

class Leaf
{
public:
	Leaf(void);
	meshData *mesh;
	RenderObject *rend;
	~Leaf(void);
	void createLeafMesh();
	void createTexCoord();
	void draw();
};

