#pragma once
#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#include "COLLECTIONS.h"
#include "KEYBOARD.h"
#include "RENDERER.h"
#include <string>;

using namespace kyb;
using namespace std;

double WIDTH = 600;
double HEIGHT = 600;

int viewPortCenter[2] = {0,0};

unsigned int initSize[2] = {1,1};
world DAN(initSize);
player nathan(DAN);

renderer scene;

counter timer;
int cycles = 0;

vector<string> tileMapVec;

void calculateViewPort(player character)
{
	viewPortCenter[0] = character.getPositionX() - WIDTH/2;
	viewPortCenter[1] = character.getPositionY() - HEIGHT/2;
}

void updateViewPort(player character)
{
	if((character.getPositionX() - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += character.getSpeed(); 
	else if((character.getPositionX() - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-= character.getSpeed(); 
	if((character.getPositionY() - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+= character.getSpeed(); 
	else if((character.getPositionY() - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-= character.getSpeed(); 
}

void display(void)
{
	glClearColor(0,0,0.1,0);
	glutInitDisplayMode(GL_DEPTH | GL_DOUBLE | GL_RGBA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	updateViewPort(nathan);

	glPointSize(62);

	//glBegin(GL_POINTS);
	//glColor3f(0,1,0);
	//glVertex2i(nathan.getPositionX(), nathan.getPositionY());
	//glEnd();
	scene.render();

	glBindTexture(GL_TEXTURE_2D, scene.textureData.getTexture());

	float textureCoords[] = {0,0, 1,0, 0,1, 0,1, 1,1, 1,0};
	float playerPos[] = {nathan.getPositionX()-32,nathan.getPositionY()-32,
		nathan.getPositionX()+32,nathan.getPositionY()-32,
		nathan.getPositionX()-32,nathan.getPositionY()+32,
		nathan.getPositionX()-32,nathan.getPositionY()+32,
		nathan.getPositionX()+32,nathan.getPositionY()+32,
		nathan.getPositionX()+32,nathan.getPositionY()-32};
	float playerCol[] = {1,1,0, 1,1,0, 0,1,1, 0,1,1, 1,0,1, 1,0,1};

	//cout << scene.textureData.texture[0] << endl;
	glVertexPointer(2, GL_FLOAT, 0, playerPos);
	glColorPointer(3, GL_FLOAT, 0, playerCol);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);
	glDrawArrays(GL_TRIANGLES, 0, 6);

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
	nathan.setSpeed(4);
	nathan = menuStates(nathan, DAN);
	//if(1 < cycles)
	//{
	//	nathan = menuStates(nathan, DAN);
	//	cycles = 0;
	//}
	//else cycles++;
	//timer.updateSystem();
}

///////////MOVE TO CLASS/////////////
vector<string> getWorldFromTextFile(string fname)
{
	vector<string> stringWorld;
	string line;
	ifstream infile;

	unsigned int lineNum = 0;

	infile.open(fname);

	while(!infile.eof())
	{
		getline(infile,line);
		if (line=="") continue; //gets ride of blank line
		stringWorld.push_back(line);
	}
	infile.close();

	return stringWorld;
}

//testing purposes
void printStringVector(vector<string> vec)
{
	for (int i = 0; i<vec.size();i++)
	{
		cout<<vec.at(i)<<endl;
	}
}

bool getPassThroughtByStr(string s)
{
	if (s == "false") return false;
	else if(s == "true") return true;
	else return false;
}

bool doubleStar(string line)
{
	return line[0]=='*' && line[1]=='*';
}

bool tripleStar(string line)
{
	return line[0]=='*' && line[1]=='*' && line[2]=='*';
}

void parseAbstractionLevels(vector<string> txtVec, world map)
{
	string title;
	int temp;
	bool search = false;
	tile tl;
	actor act;
	object ob;
	string line;
	player ply(map);

	for (int i = 0; i <txtVec.size();i++)
	{
		line = txtVec.at(i);
		
		if(doubleStar(line) && !tripleStar(line))
		{
			title = line.substr(2,line.size());
			cout<<"Title:"<<title<<endl;
		}
		else if (tripleStar(line))
		{
			search = !search;
			if (!search) 
			{
				map.addTile(tl);
				map.addObject(ob);
				map.addActor(act);
			}
			continue;
		}
		else
		{
			int index = line.find(":") +1;
			string type = line.substr(1,index-2);
			cout<<"type:"<<type<<endl;	
			string subStr = line.substr(index+1,line.size()-1);
			cout<<"subString:"<<subStr<<endl;
			unsigned int mapSize[2];

			if(type =="DESCRIPTION")
			{
				if (title =="TILE" )
				{
					cout<<"------>i am in tile discription"<<endl;
					tl.changeDescription(subStr);
				}
				else if (title == "OBJECT")
				{
					ob.changeDescription(subStr);
				}
				else if (title =="ACTOR")
				{
					act.changeDescription(subStr);
				}
				else if (title =="PLAYER")
				{
					ply.changeDescription(subStr);
				}
			}
			else if(type =="PASSABLE")
			{
				if (title =="TILE" )
				{	
					tl.changePassThrough(getPassThroughtByStr(subStr));
				}
				else if (title == "OBJECT")
				{
					ob.changePassThrough(getPassThroughtByStr(line));
				}
			}
			else if(type == "FACE")
			{
				
				if (title == "OBJECT")
				{
					if (subStr == "up") ob.changeFace(object::direction::up);
					else if (subStr == "down") ob.changeFace(object::direction::down);
					else if (subStr == "left") ob.changeFace(object::direction::left);
					else if (subStr == "right") ob.changeFace(object::direction::right);
					else ob.changeFace(object::direction::up);
				}
				else if (title =="ACTOR")
				{
					if (subStr == "up") act.changeDirection(actor::direction::up);
					else if (subStr == "down") act.changeDirection(actor::direction::down);
					else if (subStr == "left") act.changeDirection(actor::direction::left);
					else if (subStr == "right") act.changeDirection(actor::direction::right);
					else act.changeDirection(actor::direction::up);
				}
				else if (title =="PLAYER")
				{
					if (subStr == "up") ply.changeDirection(player::direction::up);
					else if (subStr == "down") ply.changeDirection(player::direction::down);
					else if (subStr == "left") ply.changeDirection(player::direction::left);
					else if (subStr == "right") ply.changeDirection(player::direction::right);
					else ply.changeDirection(player::direction::up);
				}
			}
			else if(type =="START_X")
			{
				if (title =="ACTOR") act.setPosX(stoi(subStr));
				else if (title=="PLAYER") ply.setPosX(stoi(subStr)); 
			}
			else if(type =="START_Y")
			{
				if (title =="ACTOR") act.setPosY(stoi(subStr));
				else if (title=="PLAYER") ply.setPosY(stoi(subStr)); 
			}
			else if(type == "BITMAP")
			{
				if (title =="ACTOR") act.changeBitMapName(subStr);
				else if (title=="PLAYER") ply.changeBitMap(subStr); 
			}
			else if(type =="SPEED")
			{
				if (title =="ACTOR") act.setSpeed(stoi(subStr));
				else if (title=="PLAYER") ply.setSpeed(stoi(subStr));
			}
			else if(type=="WIDTH")
			{
				if (title =="TILE_MAP") mapSize[0] = (unsigned int) stoi(subStr);
				cout<<"----------->w= "<<mapSize[0]/2<<endl;
			}
			else if(type=="HEIGHT")
			{
				if (title =="TILE_MAP")
				{
					mapSize[1]= (unsigned int) stoi(subStr);
					map.changeDimension(mapSize);
				}
			}else 
			{
				tileMapVec.push_back(line);	
			}
		}
	}	
}

void populateWorld(vector<string> map)
{

	//change all this
	unsigned int size[] = {0,map.size()};

	for (int i =0; i<map.size();i++)
	{
		for(int j = 0; j<(map.at(i)).length(); j++)
		{
			switch((map.at(i))[j])
			{
			case '0':
				DAN.setTileLocation(size, 0);
				size[0]++;
				break;
			case '1':
				DAN.setTileLocation(size, 1);	
				size[0]++;
				break;	
			}
		}
		size[0]= 0;
		size[1]--;
	}
}


//this is depreciated
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

                for (size_t i = 0; i < line.size(); i++)
                {
                        char n = line[i];

                        //cout<<"char"<<n<<endl;

                        if (n=='0'){
                                DAN.setTileLocation(size, 0); //ID = 0 -->wall
                                size[0]++;
                                //cout<<"i should be in here 0"<<endl;
                        }
                        else if(n=='1')
                        {
                                DAN.setTileLocation(size, 1);  //ID = 1 --> floor      
                                size[0]++;
                                //cout<<"i should be in here 1"<<endl;
                        }
                }
                size[0] = 0;
                size[1]--;
        }

infile.close();
}

/////////END MOVE TO CLASS///////

void main(int argv, char* argc[])
{
		resetKeys();

        tile block;
        object newBlock;

		vector<string> vec = getWorldFromTextFile("world_NEW.txt");
		//printStringVector(vec);
		parseAbstractionLevels(vec, DAN);



        //unsigned int size[] = {5,5};

        //size of text file rows,columns
        //unsigned int txtFileSize[] = {50,50};

        //DAN.changePlayerStart(size);
        player greg(DAN);
        nathan = greg;

       // block.changeDescription("HOORAY");
        //block.changePassThrough(true);

        //DAN.changeDimension(txtFileSize);

		//DAN.addTile(block);
        //DAN.printLog();

		populateWorld(tileMapVec);

		cout<<"tile map: "<<endl;
		printStringVector(tileMapVec);

		scene.worldToArray(DAN, 64);

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