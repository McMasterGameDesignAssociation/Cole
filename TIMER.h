#pragma once
#ifndef _TIMER
#define _TIMER

#include "COLLECTIONS.h"

class counter
{

private:
	int timing;
	int count;
	/*This is the number of cycles in a ms*/
	int increment;

	enum countChoice{reset, inc};

public:

	counter(void);
	
	/*This will check the timing value*/
	bool checkTiming(void);
	int getInc(void);

	void updateTiming(void);
	/*this will either inc, or reset the counter*/
	void updateCount(countChoice update);
	void updateInc(int newInc);
	void updateSystem(void);

};



#endif