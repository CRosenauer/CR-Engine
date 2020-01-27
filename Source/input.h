#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_events.h>

#include <cstdio>

#define CONTROLLER_SUPPORT

//const int to determine how many inputs are read
//note: x and y inputs on d-pads or control sticks are counted as 1 input
//ex. for implementing WASD movement you would only need 2 width, one for WS one for AD.
const int INPUTWIDTH = 4;

enum INPUTMAP
{
	INPUT_X,   //0
	INPUT_Y,   //1
	INPUT_Z,   //2
	INPUT_QUIT //3
};

class inputHandler
{
public:
	inputHandler();

	//reads inputs from user and sets input values to the internal input array: inputBus.
	void pollInputs();
	
	//sets passed array to the user's inputs
	//for reading specific inputs use enum INPUTMAP as the index.
	void getUserInputs(__int8 readInputs[INPUTWIDTH]);

	//function returns a boolean array representing if inputs have been repeated since last tick.
	//true:  input is repeated since last tick.
	//false: input is not repeated since last tick.
	//for reading specific inputs use enum INPUTMAP as the index.
	void getRepeatInputs(bool readInputs[INPUTWIDTH]);

private:
	//void loadCustomKeys();
	//to be implemented.
	//reads stored keymaps from file and applies said keys to pollInputs logic.

	//internal array for storing user inputs
	__int8 inputBus[INPUTWIDTH];

	bool repeatInput[INPUTWIDTH];

	const Uint8* currentInputs = SDL_GetKeyboardState(NULL);

	// Boolean array to store inputs for button presses
	// 0: up/down    (+/-)
	// 1: left/right (+/-)
	// 2: enter      (+)
};

#endif //INPUT_H