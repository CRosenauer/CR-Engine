#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_events.h>

#include "config.h"

enum CRE_InputMap
{
	INPUT_X,    //0
	INPUT_Y,    //1
	INPUT_ENTER //2
};

class CRE_InputHandler
{
public:
	CRE_InputHandler();

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

	const Uint8* currentInputs = NULL;

	// Boolean array to store inputs for button presses
	// 0: up/down    (+/-)
	// 1: left/right (+/-)
	// 2: enter      (+)
};

#endif //INPUT_H