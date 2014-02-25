/*
CURRENT VERSION ALPHA 0.01
VERSION NOTES
-Basic game operation (i.e. movement, basic collision detection)
-Basic file operation (i.e. fully readable files, no organization structure)
-Texturing
-Walk animations

-No level editor
-No win condition
-No lose condition
-No story elements

UPDATES REQUIRED

-Separation of the test globals from the
keyboard function (This is an NPC issue)

-Separation of the NPC animation and
update procedures

-Locking the mouse to the movement
	-An updated method will be need

-Lose condition needs to be added

-DTD, XML reader and conf reader needs to be implemented

*/

#pragma once
#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#include "COLLECTIONS.h"
//#include "RENDERER.h"

using namespace std;

//Current values for maintaining the
//The size of the screen
int WIDTH = 600;
int HEIGHT = 600;

//This is the initial centering of the view port
//Set to 0,0 since the starting position needs to be
//decided by the current map
int viewPortCenter[2] = {0,0};

//These are just test constants and are pretty self
//explanatory
unsigned int initSize[2] = {1,1};
world DAN(initSize);
player PLAYER_ONE(DAN);
bool pause = false;
bool suspicious = false;
vector<actor> actorVector;

/*
Added by Ryan and needs to be built
into its own class
*/

//NPC variables
int detectionRange = 64 * 100;
int frameCounter = 0;
int randomNumNPC;
int frameStop = 1000; //NPCs will update their direction in less frames if they hit a wall
//NPC variables

renderer scene;

//FileReading + suspcisionMeter visual - Cole
FileReader fr("world.txt");
vector<vector<int>> worldMap;
SuspicionMeter susMeter;



#include "KEYBOARD.h"
using namespace kyb;

/*
contains:
player character
	character designates the player that the view port is following

Update viewport creates an invisible box around the player which gives
the area that the camera can see
*/
void updateViewPort(player character)
{
	//The viewport encompasses 75% of the the center of the scene
	//Therefore when the chracter position reaches 25%> and <75%
	//The view port moves at the same speed as the character
	if((character.getPositionX() - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += character.getSpeed(); 
	else if((character.getPositionX() - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-= character.getSpeed(); 
	if((character.getPositionY() - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+= character.getSpeed(); 
	else if((character.getPositionY() - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-= character.getSpeed(); 
}

/*
Passive Mouse function that modifies the current hardcoded player information
and then passes it to the scene to render it
*/
void passiveMouse(int x, int y)
{
	int pos[] = {x, y};
	int dimensions[] = {WIDTH, HEIGHT};
	PLAYER_ONE.changeDirection(pos, dimensions);
	scene.animatePlayer(PLAYER_ONE, false);
}

/*
This is the obligatory display function, THE COMMENTS INSIDE
THE FUNCTION ARE IMPORTANT

Required updates:

- Removal of NPC logic and rendering
*/
void display(void)
{
	//Obligatory Set up functions
	glClearColor(0,0,0.2,0);
	glutInitDisplayMode(GL_DEPTH | GL_DOUBLE | GL_RGBA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//The Depth buffer is necessary for the transparencies to work
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);

	//Never Forget the teture initialization
	glEnable(GL_TEXTURE_2D);

	//LoadIdentiry is used to clear all current transformations (only useful on start up
	//since all movement is done by modifiying the draw and not by using transisitions)
	glLoadIdentity();
	
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	//Update the view port to maintain the camera on the player
	updateViewPort(PLAYER_ONE);

	/* (+) Drawing the NPCs
        * this will draw the NPC's and make them chase the player
        */
       
       //Added by Ryan
       
 
        /*
        This for loop makes the NPCs move
        */
		glPointSize(64);
		glBegin(GL_POINTS);
        for(unsigned int i = 0; i < actorVector.size(); i++)
		{
			double probabilities[4] = {1,1,1,1};
            glColor3f(actorVector[i].getAlert(),0.3,0.7);
               
            glVertex2i(actorVector[i].getPosition().x, actorVector[i].getPosition().y);
            actorVector[i].updateMovement(DAN);
 
  			if(actorVector[i].isFacingPlayer(PLAYER_ONE) && suspicious) actorVector[i].increaseAlert();
			else if(actorVector[i].getAlert() > 0) actorVector[i].decreaseAlert();
 
			actorVector[i].setMoving(true);
            if(actorVector[i].getAlert() == 0) {
		
			//Scatter algorithm
			int * seedy;
			seedy = new int[0];
			srand(time(NULL) * (int)&seedy[0]);
			delete[] seedy;
            randomNumNPC = rand()%100;
            //In this situation, the NPCs are out of range. They patrol the area
			//This should be migrated to the timer function
			if(actorVector[i].getIsHittingWall() == false) frameStop = 1000;
			else frameStop = 200;
 
			frameCounter++;
                       
			if(frameCounter > frameStop)
			{
				actorVector[i].changeDirection(probabilities);
				frameCounter = 0;
			}
		}
               
		//Detect movement ends here
        actorVector[i].setMoving(true);
		if(actorVector[i].isFacingPlayer(PLAYER_ONE) && actorVector[i].getAlert() > 0)
        { //if actor can see vector
			actorVector[i].setMoving(true);
			if(abs( (double) PLAYER_ONE.getPositionX() - actorVector[i].getPosition().x) > 32 || abs( (double) PLAYER_ONE.getPositionY() - actorVector[i].getPosition().y) > 32)
			{ //if the actor is greater than 32 pixels away from the player (if it isn't, there is no need to move)
				if( (abs( (double) PLAYER_ONE.getPositionX() - actorVector[i].getPosition().x) > abs( (double) PLAYER_ONE.getPositionY() - actorVector[i].getPosition().y)))
				{ //if the x is further away than the y then move x. otherwise move in y.
					if (actorVector[i].getPosition().x < PLAYER_ONE.getPositionX() + 32 )
						actorVector[i].changeDirection(Right);
					else if (actorVector[i].getPosition().x > PLAYER_ONE.getPositionX() - 32)
						actorVector[i].changeDirection(Left);
				}
				else
				{
					if (actorVector[i].getPosition().y < PLAYER_ONE.getPositionY() + 32)
						actorVector[i].changeDirection(Up);
					else if (actorVector[i].getPosition().y > PLAYER_ONE.getPositionY() - 32)
						actorVector[i].changeDirection(Down);
				}
				if(actorVector[i].getIsHittingWall() == true)
					actorVector[i].incrementDirection();
			}
			else actorVector[i].setMoving(false);
		}
	}
 
 
    /* (-) Drawing the NPCs */
	glEnd();

	//suspicsion meter stuff - Cole
	susMeter.updatePosistion(PLAYER_ONE.getPositionX(), PLAYER_ONE.getPositionY());
	susMeter.render();

	scene.render();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
	updateViewPort(PLAYER_ONE);
}

void idle(void)
{
	if(!pause)
	{
		PLAYER_ONE.setSpeed(2);
		PLAYER_ONE = menuStates(PLAYER_ONE, DAN);
	}
}

/*
Populate world reads in unformatted files and populates the current
game world

Required Updates:
-Dynamic file name
-Text file size should be determined by the
file and not the function
-The file reader should be able to handle structured
file types, specifically in 
	-XML(This will be used for data transmission of hard coded entities)
	-DTD(This is the key file that explains to the reader
	which information belongs to which class and how to handle it)
	-CONF(This will be used for the dynamic information such as 
	gamefiles, world files, object files etc.)
	-PNG(This will be used to store images)

-If time permits there should be an update added so that 
files are stored as Byte information and not as plaintext
as to allow a 4 bit shift to each character to make the file
unreadable outside of the game program

*/

void populateWorld(void)
{
	vector<vector<int>> worldMap = fr.getWorld();
	fr.print2dIntVector(worldMap);

	int n = 0;
	unsigned int mapLocation[2] = {0,0};
	
	for(int i = 0; i < worldMap.size(); i++)
	{
		for(int j = 0; j < worldMap.at(0).size(); j++)
		{	
			DAN.setTileLocation(mapLocation, worldMap.at(i).at(j));
			mapLocation[0]++;
		}
		mapLocation[1]++;
		mapLocation[0] = 0;
	}
	
}

/*
Obligatory main function

This requires a lot of clean up
*/
void main(int argv, char* argc[])
{
		worldMap = fr.getWorld();

		resetKeys();

		/*(+) NPC stuff 
		*This will initialize all the actors and push them into actorVector
		*/

		for (int i = 2; i < 5 + 2; i++){
			actor newActor(5*64,13*64, 4);
			DAN.addActor(newActor);
		}
		actorVector = DAN.getActorSet();
		//(-) NPC stuff //

		scene.setUpCharacters(7);
        tile block;
        object newBlock;

        unsigned int size[] = {5,5};

        //size of text file rows,columns
		unsigned int fileSize[] = {fr.getX(),fr.getY()};

        DAN.changePlayerStart(size);
        player greg(DAN);
        PLAYER_ONE = greg;

        block.changeDescription("HOORAY");


        DAN.changeDimension(fileSize);

		populateWorld();

		DAN.addTile(block);
		block.changePassThrough(true);
		block.changeDescription("NOT HOORAY");
		DAN.addTile(block);
		block.changePassThrough(false);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
		DAN.addTile(block);
        DAN.printLog();

		DAN.printLog();

        populateWorld();

		scene.worldToArray(DAN);
		scene.setUpPlayer("Charactersforreal.png", PLAYER_ONE, DAN);

        glutInit(&argv, argc);
        glutInitWindowSize(600,600);
        glutCreateWindow("Pure Kleptomania");
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboardInput);
		glutPassiveMotionFunc(passiveMouse);
        glutKeyboardUpFunc(keyRelease);
        glutMainLoop();
}

#endif