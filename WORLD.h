/*

_WORLD contains all of the basic data structures that will be used to control
the basic function of the world that the game will be using

the wrapper class world contains 3 sub classes tile, object, actor, which are used
to manage there respective entity type

*/

#ifndef _WORLD
#define _WORLD

#include "COLLECTIONS.h"

using namespace std;

/*
tile is used as the base unit of the world

variables
	unsigned int ID - An ID to track the tile through
			 the system

	bool passThrough - This boolean is used to
			 determine if the tile can be walked
			 over i.e. a pathway, or ones that 
			 can not be walked over i.e. a wall

	string bitMapName - This is the string that
			 will be used to determine the name
			 and the directory of the current
			 texture for the tile.
	string description - This will be used a documenting
						 tool, and will be used in the change logs
*/
class tile
{
private:

	unsigned int ID;
	bool passThrough;
	string bitMapName;
	string description;

public:

	//Modifiers
	tile(void);
	tile(bool passable, string bitMap, string newDescription);
	void setTile(bool passable, string bitMap, string newDescription);
	void changeID(unsigned int newID);
	void changePassThrough(bool passable);
	void changeBitMapName(string bitMap);
	void changeDescription(string newDescription);

	//Accessors
	int getID(void);
	bool getPassThrough(void);
	string getBitMapName(void);
	string getDescription(void);

	//Logging functions
	void printLog(void);

};

/*

The object class is used to store the information that is
contained in each object in the world, where objects
are passive but the player can interact with them
i.e. doors, security systems, shelves, etc.
enum
	direction{up, left, down, right] - This is used as a local type
									   to track the direction of an
									   object

variables
	unsigned int ID - ID is used to distinguish each object from each other
	object::direction face - Face determines the direction
							 the front of the object is facing
	bool passThrough - This determines if the player will collide with
					   the current object
	string bitMapName - This determines the directory where every
							  texture for each version of the object's
							  sprite is located
	string description - This will be used to describe the object in the
						 logs
*/
class object
{
	private:
		
		//enum direction{up, left, down, right};

		unsigned int ID;
		//direction face;
		bool passThrough;
		string bitMapName;
		string description;
	
	public:
		//Modifiers
		enum direction{up, left, down, right};
		direction face;
		object(void);
		void setObject(direction newFace, bool passable, string newBitMapName, string newDescription);
		void changeID(unsigned int newID);
		void changePassThrough(bool passable);
		void changeFace(direction face);
		void changeBitMapName(string newBitMapName);
		void changeDescription(string newDescription);

		//Accessors
		int getID(void);
		direction getFace(void);
		bool getPassThrough(void);
		string getBitMapName(void);
		string getDescription(void);

		//Logging function
		void printLog(void);

};

/*
contains
	enum direction - direction will be used to determine the direction 
					 that the actor is facing
	unsigned unsigned int ID - ID provides a unique ID for each actor so 
		    		  they can be tracked through the system
	direction face - face determines the standing direction the actor
					 is facing
	string bitMapName - bitMapName is the current name of the bitMap
						that the actor uses as a costume

The actor class is used to make instances of NPCs to be used in the world
*/
class actor
{
	private:
		
		/*This tracks the direction the actor is facing
		entities up, left, down, right*/
		//enum direction{up, left, down, right};

		unsigned int ID;
		string bitMapName;
		string description;
		int pos[2];
		int speed;

	public:
		enum direction{up, left, down, right};
		direction face;
		//Modifiers
		actor(void);
		void setSpeed(int newSpeed);
		void setPosX(int x);
		void setPosY(int y);
		void setActor(direction newFace, string newBitMapName, string newDescription);
		void changeID(unsigned int newID);
		void changeDirection(direction newFace);
		void changeBitMapName(string newbitMapName);
		void changeDescription(string newDescription);

		//Accessor
		int getID(void);
		direction getFace(void);
		string getBitMapName(void);
		string getDescription(void);

		//Logging function
		void printLog(void);

};

/*
contains
	vector<tile> tileSet - This is the set of tiles used in the world
	vector<object> objectSet - This is the set of objects used in the world
	vector<actor> actorSet - This is the set of actors used in the world
	int* tileLocations - This is the locations of all of the current tiles
	int* objectLocations - This is the locations of all of the current objects
	int* actorLocations - This is the locations of all of the current actors
	unsigned int dimensions[2] - This is the current dimensions of the world
	unsigned int playerStartingPosition[2] - This is the starting position for
	the player, making a predefined entrance will prevent the player from 
	initially being placed in a wall

world is used to control and maintain all of the in world
game elements
*/
class world
{
	private:

		vector<tile> tileSet;
		vector<object> objectSet;
		vector<actor> actorSet;
		int* tileLocations;
		int* objectLocations;
		int* actorLocations;
		unsigned int dimensions[2];
		unsigned int playerStartLocation[2];

	public:

		world(unsigned int size[2]);
		void setTiles(vector<tile> newTileSet);
		void setObjects(vector<object> newObjectSet);
		void setActor(vector<actor> newActorSet);
		void changeDimension(unsigned int size[2]);
		void addTile(tile block);
		void addObject(object block);
		void addActor(actor character);
		void removeTile(unsigned int ID);
		void removeObject(unsigned int ID);
		void removeActor(unsigned int ID);
		void getLog(void);
		void setTileLocation(unsigned int pos[2], unsigned int ID);
		void setObjectLocation(unsigned int pos[2], unsigned int ID);
		void setActorLocation(unsigned int pos[2], unsigned int ID);
		void swapTile(tile newTile, int ID);
		void swapObject(object newObject, int ID);
		void swapActor(actor newCharacter, int ID);

		void printLog(void);
		
		tile getTile(unsigned int ID);
		object getObject(unsigned int ID);
		actor getCharacter(unsigned int ID);
		vector<tile> getTileSet(void);
		vector<object> getObjectSet(void);
		vector<actor> getActorSet(void);

		bool getTileCollision(unsigned int ID);
		bool getObjectCollision(unsigned int ID);
		unsigned int* getPlayerStart(void);

		void changeTilePassthrough(unsigned int ID, bool passable);
		void changeObjectPassthrough(unsigned int ID, bool passable);
		void changePlayerStart(unsigned int playerLocation[2]);
		
		int checkTileMap(unsigned int pos[2]);
		int checkObjectMap(unsigned int pos[2]);
		int checkActorMap(unsigned int pos[2]);

		int getX(void);
		int getY(void);
};

class player
{
private:
	unsigned int position[2];
	string bitMapName;
	string description;
	int speed;

public:
	enum direction{up, left, down, right};
	direction face;

	player(world map);
	int getSpeed(void);
	unsigned int getPositionX(void);
	unsigned int getPositionY(void);
	string getBitMap(void);
	string getDescription(void);
	void changeDirection(direction newFace);
	void changeDescription(string newDescription);
	void changePosition(unsigned int pos[2]);
	void setPosX(int x);
	void setPosY(int y);
	void changeBitMap(string newBitMap);
	void checkMovement(world map, int x, int y);
	void setSpeed(int movement);

};

#endif // !_WORLD