#pragma once
#ifndef _KEYBOARD_MACHINE
#define _KEYBOARD_MACHINE

#include "COLLECTIONS.h"

namespace kyb
{
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

	/* This will be the clear keys function */
	void resetKeys(void) {for(int i = 0; i < 8; i++) keys[i] = false;}

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
		cout << time(0) << endl;
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
		cout << time(0) << endl;
	}

	/* This is the state machine to run the keyboard in the idleFunc */
	player menuStates(player character, world map)
	{
		//W and A
		if(keys[0] && keys[2])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 0, 1);
				character.checkMovement(map, -1, 0);
			}
		}
		//W and D
		else if(keys[0] && keys[3])
		{
			if(keys[6]);
			else
			{
				character.checkMovement(map, 0, 1);
				character.checkMovement(map, 1, 0);
			}
		}
		//S and A
		else if(keys[1] && keys[2])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, -1, 0);
				character.checkMovement(map, 0, -1);
			}

		}
		//S and D
		else if(keys[1] && keys[3])
		{
			if(keys[6]);
			else 
			{
				character.checkMovement(map, 1, 0);
				character.checkMovement(map, 0, -1);
			}

		}
		//W
		else if(keys[0])
		{
			if(keys[6]);
			else character.checkMovement(map, 0, 1);
		}
		//S
		else if(keys[1])
		{
			if(keys[6]);
			else character.checkMovement(map, 0, -1);
		}
		//A
		else if(keys[2])
		{
			if(keys[6]);
			else character.checkMovement(map, -1, 0);
		}
		//D
		else if(keys[3])
		{
			if(keys[6]);
			else character.checkMovement(map, 1, 0);
		}
		//Action or E key
		else if(keys[4]);
		//Menu or Q key
		else if(keys[7]);
		return character;

	}
}
#endif