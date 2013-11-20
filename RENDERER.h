#pragma once

#ifndef _RENDERER
#define _RENDERER

#include "COLLECTIONS.h"


class renderer
{
public:
	renderer(void);
	void addPoint(int point[2]);
	void addColor(int color[3]);
	void addTile(int center[2], int color[3], int size);
	void render(void);
	void printPoint(int pos);
	void clearArrays(void);
	void worldToArray(world gameSpace, int resolution);
	void testRender(void);
	image textureData;
	~renderer(void);

private:
	int* vertices;
	double* colors;
	vector<int*> tempVertices;
	vector<double*> tempColors;
	bool buildOk;
	void buildArrays();

};

#endif