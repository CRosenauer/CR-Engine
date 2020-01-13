#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_events.h>

#include <new>
#include <cstdio>

extern const int INPUTWIDTH;
extern __int8* inputBus;

class inputHandler
{
public:
	inputHandler();

	void pollInputs();
	//reads inputs from user and 

	//destructor
	//deletes memory from inputbus
	//will likely be removes later was inputBus doens't need to be heap memory
	~inputHandler();

private:
	//void loadCustomKeys();
	//to be implemented.
	//reads stored keymaps from file and applies said keys to pollInputs logic.

	const Uint8* currentInputs = SDL_GetKeyboardState(NULL);

	// Boolean array to store inputs for button presses
	// 0: up/down    (+/-)
	// 1: left/right (+/-)
	// 2: enter      (+)
};

#endif //INPUT_H