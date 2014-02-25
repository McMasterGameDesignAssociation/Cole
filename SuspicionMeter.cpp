#include "SuspicionMeter.h"


SuspicionMeter::SuspicionMeter(void)
{
	offsetX = 32;
	offsetY = 32;
	barWidth = 60;
	barHeight = 10;
	suspicionValue = 10;
}

void SuspicionMeter::updatePosistion(int newX, int newY)
{
	this->x = newX-offsetX;
	this->y = newY+offsetY;
}

void SuspicionMeter::updateSuspicion(int suspicionValue)
{
	this->suspicionValue = suspicionValue;
}

void SuspicionMeter::render(void)
{
	//glquads for now
	//outline
	//glClearColor(0,0,0,0);
	glColor3i(1,0,0);
	glBegin(GL_QUADS);
		glVertex2i(x,y);
		glVertex2i(x + barWidth,y);
		glVertex2i(x + barWidth,y + barHeight);
		glVertex2i(x,y + barHeight);

		glVertex2i(x,y);
		glVertex2i(x + suspicionValue,y);
		glVertex2i(x + suspicionValue,y + barHeight);
		glVertex2i(x,y + barHeight);

		
	glEnd();
}

