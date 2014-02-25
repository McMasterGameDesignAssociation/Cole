#pragma once

#include<GL/glut.h>

using namespace std;
class SuspicionMeter
{
public:
	SuspicionMeter(void);
	void updatePosistion(int newX, int newY);
	void render(void);
	void updateSuspicion(int suspicsionValue);
private:
	int x;
	int y;
	int offsetX;
	int offsetY;
	unsigned int barWidth;
	unsigned int barHeight;
	unsigned int suspicionValue;
};

