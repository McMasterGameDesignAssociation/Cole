#ifndef _KEYBOARD_MACHINE
#define _KEYBOARD_MACHINE

#include <GL\freeglut.h>
#include <GL\GL.h>
#include "WORLD.h"
#include <iostream>

#include <fstream>
#include <string>
#include <cstring>

/****

0 - W
1 - S
2 - A
3 - D
4 - Action/E
5 - Inventory/Q
6 - Run/Walk/Shift
7 - MainMenu/ESC

***/
bool keys[8];

/*
This will be the clear keys function
*/
void resetKeys(void) 
{
	for(int i = 0; i < 8; i++) keys[i] = false;
}

void keyRelease(unsigned char keyStroke, int x, int y)
{
	switch(keyStroke)
	{
	case 'w': keys[0] = false;
		break;

	case 's': keys[1] = false;
		break;

	case 'a': keys[2] = false;
		break;

	case 'd': keys[3] = false;
		break;

	case 'e': 
	case 'q': 
	default: resetKeys();
		break;
	}	
}

/*

Basic input for the keyboard

*/
void keyboardInput(unsigned char keyStroke, int x, int y)
{
	switch(keyStroke)
	{
	case 'w': keys[0] = true;
		keys[1] = false;
		break;

	case 's': keys[0] = false;
		keys[1] = true;
		break;

	case 'a': keys[2] = true;
		keys[3] = false;
		break;

	case 'd': keys[2] = false;
		keys[3] = true;
		break;

	case 'e': resetKeys();
		keys[4] = true;
		break;

	case 'q': resetKeys();
		keys[5] = true;
		break;

	default: break;
	}
}

/*
This is the state machine to run the keyboard in the idleFunc
*/
int speed = 8;
player menuStates(player character, world map)
{
	//W and A
	if(keys[0] && keys[2])
	{
		if(keys[6]);
		else 
		{
			character.checkMovement(map, 0, speed);
			character.checkMovement(map, -speed, 0);
		}
	}
	//W and D
	else if(keys[0] && keys[3])
	{
		if(keys[6]);
		else
		{
			character.checkMovement(map, 0, speed);
			character.checkMovement(map, speed, 0);
		}
	}
	//S and A
	else if(keys[1] && keys[2])
	{
		if(keys[6]);
		else 
		{
			character.checkMovement(map, -speed, 0);
			character.checkMovement(map, 0, -speed);
		}

	}
	//S and D
	else if(keys[1] && keys[3])
	{
		if(keys[6]);
		else
		{ 
			character.checkMovement(map, 0, -speed);
			character.checkMovement(map, speed,0);
		}
	}
	//W
	else if(keys[0])
	{
		if(keys[6]);
		else character.checkMovement(map, 0, speed);
	}
	//S
	else if(keys[1])
	{
		if(keys[6]);
		else character.checkMovement(map, 0, -speed);
	}
	//A
	else if(keys[2])
	{
		if(keys[6]);
		else character.checkMovement(map, -speed, 0);
	}
	//D
	else if(keys[3])
	{
		if(keys[6]);
		else character.checkMovement(map, speed, 0);
	}
	//Action or E key
	else if(keys[4]);
	//Menu or Q key
	else if(keys[7]);
	return character;

}

#endif

#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA


//#include "keyboardFunctions.cpp"

using namespace std;

double WIDTH = 600;
double HEIGHT = 600;

int viewPortCenter[2] = {0,0};

unsigned int initSize[2] = {1,1};
world DAN(initSize);
player nathan(DAN);

void calculateViewPort(player character)
{
	viewPortCenter[0] = character.getPositionX() - WIDTH/2;
	viewPortCenter[1] = character.getPositionY() - HEIGHT/2;
}

void updateViewPort(player character)
{
	if((character.getPositionX() - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += 8; 
	else if((character.getPositionX() - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-=8; 
	if((character.getPositionY() - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+=8; 
	else if((character.getPositionY() - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-=8; 

}

void display(void)
{
	glClearColor(0,0,0.1,0);
	glutInitDisplayMode(GL_DEPTH | GL_FLOAT | GL_RGBA | GL_DOUBLEBUFFER);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	updateViewPort(nathan);
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
	glutSwapBuffers();
	glFlush();
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
	calculateViewPort(nathan);
}

void idle(void)
{
	nathan = menuStates(nathan, DAN);
}


void populateWorld(unsigned int txtFileSize[])
{
	string fname = "world.txt";
	string line;
	ifstream infile;

	unsigned int lineNum = 0;

	unsigned int size[] = {0,txtFileSize[1]};

	infile.open(fname);

	while(!infile.eof())
	{

		getline(infile,line);

		cout<<line<<endl;

		for (size_t i =0; i<line.size();i++)
		{

			char n = line[i];

			//cout<<"char"<<n<<endl;

			if (n=='0'){
				DAN.setTileLocation(size, 0);
				size[0]++;
				//cout<<"i should be in here 0"<<endl;
			}
			else if(n=='1')
			{
				DAN.setTileLocation(size, 1);	
				size[0]++;
				//cout<<"i should be in here 1"<<endl;
			}
		}
		size[0] = 0;
		size[1]--;
	}

infile.close();
}


void main(int argv, char* argc[])
{
	resetKeys();

	tile block;
	object newBlock;

	unsigned int size[] = {5,5};

	//size of text file rows,columns
	unsigned int txtFileSize[] = {50,50};

	DAN.changePlayerStart(size);
	player greg(DAN);
	nathan = greg;


	//this should be wrapped to the text file


	block.changeDescription("HOORAY");
	block.changePassThrough(true);

	DAN.changeDimension(txtFileSize);
	//cout << DAN.getTileCollision(0) << endl;
	
	//size[0] = 0;
	//size[1] = 0;

	DAN.addTile(block);
	DAN.printLog();

	populateWorld(txtFileSize);

/*
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
	size[1] = 18; //18
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
	*/

	glutInit(&argv, argc);
	glutInitWindowSize(600,600);
	glutCreateWindow("Pure Kleptomania");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardInput);
	glutKeyboardUpFunc(keyRelease);
	glutMainLoop();
}

#endif