#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_events.h>

#include <cstdio>

//const int to determine how many inputs are read
//note: x and y inputs on d-pads or control sticks are counted as 1 input
//ex. for implementing WASD movement you would only need 2 width, one for WS one for AD.
const int INPUTWIDTH = 3;

enum INPUTMAP
{
	INPUT_X,   //0
	INPUT_Y,   //1
	INPUT_QUIT //2
};

class inputHandler
{
public:
	inputHandler();

	//reads inputs from user and sets input values to the internal input array: inputBus.
	void pollInputs();
	
	//function takes an array and 
	void getUserInputs(__int8 readInputs[INPUTWIDTH]);

private:
	//void loadCustomKeys();
	//to be implemented.
	//reads stored keymaps from file and applies said keys to pollInputs logic.

	//internal array for storing user inputs
	__int8 inputBus[INPUTWIDTH];

	const Uint8* currentInputs = SDL_GetKeyboardState(NULL);

	// Boolean array to store inputs for button presses
	// 0: up/down    (+/-)
	// 1: left/right (+/-)
	// 2: enter      (+)
};

#endif //INPUT_H