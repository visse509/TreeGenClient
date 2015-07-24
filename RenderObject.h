
#pragma once
#include "meshdata.h"
#include "textureData.h"
class RenderObject
{
public:
	RenderObject(meshData *_m,TextureData *_t);
	void draw(void);
	void initShader();
	TextureData* getT();
	meshData* getM();
	void clear();
	void setTexture(TextureData *_t);
	~RenderObject(void);
private:
	meshData *m;
	TextureData *t;
};

