#pragma once
#ifndef _WORLD_METHODS
#define _WORLD_METHODS

#include "WORLD.h"

///TILE METHODS
tile::tile(void)
{
	ID = 0;
	passThrough = false;
	bitMapName = "None";
	description = "This is an empty tile";
}

/*
inputs
	unsigned int newID - The ID that will replace the
				current ID
	bool passable - This the boolean that 
					determines passThrough
	string bitMap - This sets the new bit map
					directory

setTile is used to completely change an existing tile
*/
tile::tile(bool passable, string bitMap, string newDescription)
{
	passThrough = passable;
	bitMapName = bitMap;
	description = newDescription;
}

/*
inputs
	unsigned int newID - The ID that will replace the
				current ID
	bool passable - This the boolean that 
					determines passThrough
	string bitMap - This sets the new bit map
					directory

setTile is used to completely change an existing tile
*/
void tile::setTile(bool passable, string bitMap, string newDescription)
{
	passThrough = passable;
	bitMapName = bitMap;
	description = newDescription;
}

/*
input
	void
output
	void

printLog is used to print the current
values stored in the tile to the prompt

*/
void tile::printLog(void)
{
	cout << "Current tile: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Bit map name: " << bitMapName << endl << endl;
}

//Please do not use this function it is designed to be private
void tile::changeID(unsigned int newID) {ID = newID;}
void tile::changePassThrough(bool passable) {passThrough = passable;}
void tile::changeBitMapName(string bitMap) {bitMapName = bitMap;}
void tile::changeDescription(string newDescription) {description = newDescription;}
int tile::getID(void) {return ID;}
bool tile::getPassThrough(void) {return passThrough;}
string tile::getBitMapName(void) {return bitMapName;}
string tile::getDescription(void) {return description;}


///OBJECT METHODS
object::object(void)
{
	ID = 0;
	face = up;
	passThrough = false;
	bitMapName = "None";
	description = "This is an empty object";
}

void object::setObject(direction newFace, bool passable, string newBitMapName, string newDescription)
{
	face = newFace;
	passThrough = passable;
	bitMapName = newBitMapName;
	description = newDescription;
}

void object::printLog(void)
{
	cout << "Current object: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Pass through: " << passThrough << endl;
	cout << "Bit map: " << bitMapName << endl;
	cout << "Face: " << face << endl << endl;
}

//Please do not use this function it is designed to be private
void object::changeID(unsigned int newID) {ID = newID;}
void object::changePassThrough(bool passable){passThrough = passable;}
void object::changeFace(direction newFace){face = newFace;}
void object::changeBitMapName(string newbitMapName) {bitMapName = newbitMapName;}
void object::changeDescription(string newDescription) {description = newDescription;}

int object::getID(void) {return ID;}
object::direction object::getFace(void) {return face;}
bool object::getPassThrough(void) {return passThrough;}
string object::getBitMapName(void) {return bitMapName;}


///ACTOR METHODS
actor::actor(void)
{
	ID = 0;
	face = up;
	bitMapName = "None";
	description = "This is an empty character";
}

/*
inputs
	direction newFace - This defines the new direction of an actor
	string newBitMapName - This defines the new bit map file name
	string newDescription - This will set the new description of the
							character
output
	void
This function changes the current actor to the new one specified
*/
void actor::setActor(direction newFace, string newBitMapName, string newDescription)
{
	face = newFace;
	bitMapName = newBitMapName;
	description = newDescription;
}

/*
inputs
	void
output
	void
This function prints the change log for the current actor
*/
void actor::printLog(void)
{
	cout << "Current actor: " << description << endl;
	cout << "ID: "<< ID << endl;
	cout << "Bit map name: " << bitMapName << endl << endl;
}

//This function should be private
void actor::setPosX(int x){pos[0] = x;}
void actor::setPosY(int y){pos[1] = y;}
void actor::setSpeed(int newSpeed){speed = newSpeed;}
void actor::changeID(unsigned int newID) {ID = newID;}
void actor::changeDirection(direction newFace) {face = newFace;}
void actor::changeBitMapName(string newbitMapName) {bitMapName = newbitMapName;}
void actor::changeDescription(string newDescription) {description = newDescription;}
string actor::getDescription(void) {return description;}
int actor::getID(void) {return ID;}
actor::direction actor::getFace(void) {return face;}
string actor::getBitMapName(void) {return bitMapName;}

player::player(world map)
{
	unsigned int* temp;
	temp = map.getPlayerStart();
	position[0] = temp[0]*64, position[1] = temp[1]*64;
	bitMapName = "None";
	description = "This is an empty player";
	speed = 0;
}

unsigned int player::getPositionX(void) {return position[0];}
unsigned int player::getPositionY(void) {return position[1];}
int player::getSpeed(void) {return speed;}

string player::getBitMap(void) {return bitMapName;}
string player::getDescription(void) {return description;}
void player::setSpeed(int movement) {speed = movement;}
void player::changeDescription(string newDescription) {description = newDescription;}
void player::changePosition(unsigned int pos[2]) {position[0] = pos[0], position[1] = pos[1];}
void player::changeDirection(direction newFace) {face = newFace;}
void player::setPosX(int x){position[0] = x;}
void player::setPosY(int y){position[1] = y;}
void player::changeBitMap(string newBitMap) {bitMapName = newBitMap;}

/*
inputs
	void
output
	void
This function checks the current player's position against the tiles and the object
layers to check if motion is possible. This is done by taking the X and Y value of the
player and then dividing by the square 64 then checking it against the tile map at 
that location tileLocation(x,y) = posX/64, posY/64
*/
void player::checkMovement(world map, int x, int y)
{
	unsigned int posOne[2];
	unsigned int posTwo[2];
	unsigned int posThree[2];
	unsigned int posFour[2];
	int speed  = getSpeed();

	x = (x >= 1) ? speed : x;
	x = (x <= -1) ? -speed : x;
	y = (y >= 1) ? speed : y;
	y = (y <= -1) ? -speed : y;
	
	speed = 64 - speed;


	//This is a check of the lower bound of movement
	posOne[0] = (x + getPositionX())/64, posOne[1] = (y + getPositionY())/64;
	//This is a check of the upper bound of movement
	posTwo[0] = (x + speed + getPositionX())/64, posTwo[1] = (y + speed + getPositionY())/64;

	//This is a check of the lower bound of movement
	posThree[0] = (x + getPositionX())/64, posThree[1] = (y + speed + getPositionY())/64;
	//This is a check of the upper bound of movement
	posFour[0] = (x + speed + getPositionX())/64, posFour[1] = (y + getPositionY())/64;

	if(map.checkTileMap(posOne) && map.checkTileMap(posTwo) && map.checkTileMap(posThree) && map.checkTileMap(posFour)) 
	{
		posOne[0] = x + getPositionX(), posOne[1] = y + getPositionY();
		changePosition(posOne);
	}
}

/*
inputs
	unsigned int size[2] - This is the size of the world you are building
						   specifying the x and y values respectively
outputs void
This function clears all of the arrays and sets, and then builds a map
that contains only empty tiles, objects, and actors
*/
world::world(unsigned int size[2])
{
	tileSet.clear();
	objectSet.clear();
	actorSet.clear();
	
	delete[] tileLocations;
	delete[] objectLocations;
	delete[] actorLocations;

	dimensions[0] = unsigned int(size[0]);
	dimensions[1] = unsigned int(size[1]);

	tileLocations = new int[size[0]*size[1]];
	objectLocations = new int[size[0]*size[1]];
	actorLocations = new int[size[0]*size[1]];
	
	tile block;
	addTile(block);
	
	object objectBlock;
	addObject(objectBlock);

	actor character;
	addActor(character);
	unsigned int temp[2];
	
	for(int i = 0; i < dimensions[0]; i++)
	{
		for(int j =0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
			setActorLocation(temp, 0);
		}
	}
	playerStartLocation[0] = dimensions[0] - 1;
	playerStartLocation[1] = dimensions[1] - 1;
}

tile world::getTile(unsigned int ID) {return tileSet.at(ID);}
object world::getObject(unsigned int ID) {return objectSet.at(ID);}
actor world::getCharacter(unsigned int ID) {return actorSet.at(ID);}
vector<tile> world::getTileSet(void) {return tileSet;}
vector<object> world::getObjectSet(void) {return objectSet;}
vector<actor> world::getActorSet(void) {return actorSet;}
bool world::getTileCollision(unsigned int ID) {return tileSet.at(ID).getPassThrough();}
bool world::getObjectCollision(unsigned int ID) {return objectSet.at(ID).getPassThrough();}

/*
inputs
	unsigned int size[2] - This is the new dimensions of the world
outputs
	void

This function resizes the dimensions of current world, by resizing
the tile, object and actor maps
*/
void world::changeDimension(unsigned int size[2])
{
	dimensions[0] = unsigned int(size[0]);
	dimensions[1] = unsigned int(size[1]);

	delete[] tileLocations;
	delete[] objectLocations;
	delete[] actorLocations;

	tileLocations = new int[size[0]*size[1]];
	objectLocations = new int[size[0]*size[1]];
	actorLocations = new int[size[0]*size[1]];
	unsigned int temp[2];
	/*
	This will be updated later so that the existing 
	map will be maintained in the new map
	*/
	for(int i = 0; i < dimensions[0]; i++)
	{
		for(int j =0; j < dimensions[1]; j++) 
		{
			temp[0] = i, temp[1] = j;
			setTileLocation(temp, 0);
			setObjectLocation(temp, 0);
			setActorLocation(temp, 0);
		}
	}
	playerStartLocation[0] = dimensions[0] - 1;
	playerStartLocation[1] = dimensions[1] - 1;
}

void world::changeTilePassthrough(unsigned int ID, bool passable) {tileSet.at(ID).changePassThrough(passable);}
void world::changeObjectPassthrough(unsigned int ID, bool passable) {objectSet.at(ID).changePassThrough(passable);}
void world::setTiles(vector<tile> newTileSet) {tileSet = newTileSet;}
void world::setObjects(vector<object> newObjectSet) {objectSet = newObjectSet;}
void world::setActor(vector<actor> newActorSet) {actorSet = newActorSet;}

/*
inputs
	tile block
outputs
	void
addTile adds a new tile to the tile set, maintaining order, and therefore
making sure that all tiles still have a unique ID
*/
void world::addTile(tile block) 
{
	block.changeID(tileSet.size());
	tileSet.push_back(block);
}

/*
inputs
	object block
outputs
	void
addObject adds a new object to the object set, maintaining order, and therefore
making sure that all objects still have a unique ID
*/
void world::addObject(object block) 
{
	block.changeID(objectSet.size());
	objectSet.push_back(block);
}

/*
inputs
	actor character
outputs
	void
addObject adds a new actor to the actor set, maintaining order, and therefore
making sure that all actors still have a unique ID
*/
void world::addActor(actor character)
{
	character.changeID(actorSet.size());
	actorSet.push_back(character);
}

/*

The removal functions are unnecessary at the moment
but I will leave this prototyped incase we end up
adding in a GUI for world building

void world::removeTile(unsigned int ID) 
{
	tileSet.erase(tileSet.begin() + ID);
	for(int i = ID; i < tileSet.size(); i++) tileSet.at(i).changeID(i);
}

void world::removeObject(unsigned int ID) 
{
	objectSet.erase(objectSet.begin() + ID);
	for(int i = ID; i < objectSet.size(); i++) objectSet.at(i).changeID(i);
}

void world::removeActor(unsigned int ID)
{
	actorSet.erase(actorSet.begin() + ID);
	for(int i = ID; i < actorSet.size(); i++) actorSet.at(i).changeID(i);
}
*/

/*
inputs
	tile newTile - This is the new tile to be used in the tile set
	int ID - This is the position that new tile will be stored
This function will overwrite an existing tile in the tile set
*/
void world::swapTile(tile newTile, int ID)
{
	newTile.changeID(ID);
	if(ID > tileSet.size());
	else tileSet.at(ID) = newTile;
}

/*
inputs
	object newObject - This is the new object to be used in the object set
	int ID - This is the position that new object will be stored
This function will overwrite an existing object in the object set
*/
void world::swapObject(object newObject, int ID)
{
	newObject.changeID(ID);
	if(ID > objectSet.size());
	else objectSet.at(ID) = newObject;
}

/*
inputs
	object newCharacter - This is the new actor to be used in the actor set
	int ID - This is the position that new actor will be stored
This function will overwrite an existing actor in the object set
*/
void world::swapActor(actor newCharacter, int ID)
{
	newCharacter.changeID(ID);
	if(ID > actorSet.size());
	else actorSet.at(ID) = newCharacter;
}

//x are the columns and y are the rows
/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkTileMap(unsigned int pos[2]) 
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return 0;
	ID = tileLocations[pos[0] + pos[1]*dimensions[0]];
	return ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkObjectMap(unsigned int pos[2]) 
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return NULL;
	ID = objectLocations[pos[0] + pos[1]*dimensions[0]];
	return ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
outputs
	integer ID of what ever is located in the tile that the user is checking
This function checks the map in the world and returns the ID of the entity in the
space it is viewing

	*This function needs to have error checking added to make sure that the user 
does not check for spaces that do not exist
*/
int world::checkActorMap(unsigned int pos[2])
{
	unsigned int ID;
	//If the map has spaces outside of the range then they are empty tiles
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]) return NULL;
	ID = actorLocations[pos[0] + pos[1]*dimensions[0]];
	return ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setTileLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1]);
	else tileLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setObjectLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1] || objectSet.size() < ID);
	else objectLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

/*
inputs 
	unsigned int pos[2] - This is the position on the map that is being checked
	int ID - This sets the ID of the entity positioned at that position
output
	void
This function sets the position of the entity in the world
*/
void world::setActorLocation(unsigned int pos[2], unsigned unsigned int ID)
{
	if(pos[0] > dimensions[0] || pos[1] > dimensions[1] || actorSet.size() < ID);
	else actorLocations[pos[0] + pos[1]*dimensions[0]] = ID;
}

//getX returns the world's x dimension size
int world::getX(void) {return dimensions[0];}
//getY returns the world's y dimension size
int world::getY(void) {return dimensions[1];}

/*
inputs
	void
outputs
	void
This function prints a complete report of all of the
entities in the world
*/
void world::printLog(void)
{
	cout << "Current world" << endl;
	cout << "Sizes " << dimensions[0] << " " << dimensions[1] << endl << endl;
	for(int i = 0; i < tileSet.size(); i++) tileSet.at(i).printLog();
	for(int i = 0; i < objectSet.size(); i++) objectSet.at(i).printLog();
	for(int i = 0; i < actorSet.size(); i++) actorSet.at(i).printLog();
}

void world::changePlayerStart(unsigned int playerLocation[2]) {playerStartLocation[0] = playerLocation[0], playerStartLocation[1] = playerLocation[1];}
unsigned int* world::getPlayerStart(void) {return playerStartLocation;}

#endif