#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#include <GL\freeglut.h>
#include <GL\GL.h>
#include <iostream>
#include "WORLD.h"

using namespace std;

tile gergory;
unsigned int initSize[2] = {1,1};
world DAN(initSize);
double* mallColors;
double* mall;
double WIDTH = 600;
double HEIGHT = 600;
double newX = 0;
double newY = 0;
player nathan(DAN);

void display(void)
{
	glClearColor(0,0,0,0);
	glutInitDisplayMode(GL_DEPTH|GL_FLOAT|GL_RGBA);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluOrtho2D(newX,WIDTH + newX, newY, HEIGHT + newY);
	glViewport(0,0,WIDTH, HEIGHT);

	//glColorPointer(3*DAN.getX()*DAN.getY(), GL_FLOAT, 0 , mallColors);
	//glVertexPointer(2*DAN.getX()*DAN.getY(), GL_INT, 0, mall);

	//glDrawArrays(GL_POINTS,0, 2*DAN.getX()*DAN.getY());
	glColor3f(1,1,1);
	glPointSize(62);
	glBegin(GL_POINTS);
	unsigned int pos[2];
	glColor3f(0,1,0);
	glVertex2i(nathan.getPositionX(), nathan.getPositionY());
	for(int i = 0; i < DAN.getY(); i++)
	{
		pos[1] = i;
		for(int j = 0; j < DAN.getX(); j++)
		{
			pos[0] = j;
			if(DAN.getTileCollision(DAN.checkTileMap(pos))) glColor3f(1,1,1);
			else glColor3f(1,0,0);
			glVertex2i(j*64,i*64);
		}
	}
	glEnd();

	glutPostRedisplay();
	glFlush();
}

void populateWorld(world map)
{
	int x = map.getX();
	int y = map.getY();
	mallColors = new double[3*x*y];
	mall = new double[3*x*y];
	unsigned int pos[2];
	for(int i = 0; i < x; i++)
	{
		pos[0] = i;
		for(int j = 0; j < y; j++)
		{
			pos[1] = j;
			if(map.checkTileMap(pos) == 0)
			{
				mallColors[3*(i + j*y)] = 0;
				mallColors[3*(i + j*y) + 1] = 0;
				mallColors[3*(i + j*y) + 2] = 1;
			}
			else
			{
				mallColors[3*(i + j*y)] = 1;
				mallColors[3*(i + j*y) + 1] = 1;
				mallColors[3*(i + j*y) + 2] = 1;
			}
			mall[3*(i + j*y)] = x/100;
			mall[3*(i + j*y) + 1] = y/100;
			mall[3*(i + j*y) + 2] = 0;
		}
	}
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
}


void updateViewPort(void)
{
	if ((nathan.getPositionY()-newY)>0.75*HEIGHT) {
		newY+=8;
	} 
	if ((nathan.getPositionY()-newY)<0.25*HEIGHT){
		newY-=8;
	}
	if ((nathan.getPositionX()-newX)>0.75*WIDTH){
		newX+=8;
	}
	if ((nathan.getPositionX()-newX)<0.25*WIDTH){
		newX-=8;
	}

	cout<<"x player pos "<<nathan.getPositionX()<<endl;
	cout<<"y player pos "<<nathan.getPositionY()<<endl;
}

void keyboard(unsigned char key, int x, int y)
{
	if(key == 'w'){
		nathan.checkMovement(DAN, 0 , 8);
		updateViewPort();
	}
	else if(key == 's'){
		nathan.checkMovement(DAN, 0 , -8);
		updateViewPort();
	}
	if(key == 'a')
	{
		nathan.checkMovement(DAN, -8 , 0);
		updateViewPort();
	}
	else if(key == 'd'){
		nathan.checkMovement(DAN, 8, 0);
		updateViewPort();
	}
	if (key == 'y') newY+=64;
	else if(key == 'h') newY-=64;
	else if(key == 'g') newX-=64;
	else if(key == 'j') newX+=64;

}


void main(int argv, char* argc[])
{
	tile block;

	object newBlock;

	unsigned int size[] = {5,5};

	//DAN.changePlayerStart(
	DAN.changePlayerStart(size);
	player greg(DAN);
	nathan = greg;

	//DAN.changeTilePassthrough(1, true);
	//DAN.changeObjectPassthrough(0, true);

	size[0] = 30;
	size[1] = 30;

	block.changeDescription("HOORAY");
	block.changePassThrough(true);

	DAN.changeDimension(size);
	cout << DAN.getTileCollision(0) << endl;
	size[0] = 5;
	size[1] = 5;

	DAN.addTile(block);
	DAN.printLog();
	for(int j = 0; j < 19; j++)
	{
		for(int i = 0; i < 19; i++)
		{
			DAN.setTileLocation(size, 1);
			size[0]++;
		}
		size[1]++;
		size[0]-=19;
	}
	size[1] = 18;
	size[0] = 6;
	DAN.setTileLocation(size, 0);

	size[1] = 17;
	size[0] = 6;
	DAN.setTileLocation(size, 0);

	size[1] = 17;
	size[0] = 7;
	DAN.setTileLocation(size, 0);

	size[1] = 18;
	size[0] = 7;
	DAN.setTileLocation(size, 0);

	size[1] = 7;
	size[0] = 7;
	DAN.setTileLocation(size, 0);
	populateWorld(DAN);

	for(int i = DAN.getX() - 1; i > 0; i--)
	{
		size[1] = i;
		for(int j = 0; j < DAN.getY(); j++)
		{
			size[0] = j;
			cout << (DAN.checkTileMap(size));
		}
		cout << endl;
	}

	glutInit(&argv, argc);
	glutInitWindowSize(600,600);
	glutCreateWindow("Pure Kleptomania");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

#endif