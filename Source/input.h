#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_events.h>

#include <cstdio>


/*
	Note to future me:
	read SDL's implementation before you go messing around in stuff
	like really.

	read up on SDL_RegisterEvents
*/


class inputHandler
{
public:
	inputHandler();

	inputHandler(short numberOfInputs, __int8*& input);

	void pollInputs();
	//reads inputs from user and 


private:
	//void loadCustomKeys();
	//to be implemented.
	//reads stored keymaps from file and applies said keys to pollInputs logic.

	//internal event for storing events from event queue.

	short numberOfInputs = 3;

	__int8* inputBus;
	// Boolean array to store inputs for button presses
	// 0: up/down    (+/-)
	// 1: left/right (+/-)
	// 2: enter      (+)
};

#endif //INPUT_H