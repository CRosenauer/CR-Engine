#include "input.h"

inputHandler::inputHandler()
{
	//To implement: load keymap from file.

	for (int i = 0; i < INPUTWIDTH; i++)
	{
		inputBus[i] = 0;
		repeatInput[i] = false;
	}
		
}

void inputHandler::pollInputs()
{
	__int8 prevInput[INPUTWIDTH];

	for (int i = 0; i < INPUTWIDTH; i++)
	{
		prevInput[i] = inputBus[i];
		inputBus[i] = 0;
	}
		

	if (currentInputs[SDL_SCANCODE_D])
	{
		inputBus[INPUT_X]++;
	}

	if (currentInputs[SDL_SCANCODE_A])
	{
		inputBus[INPUT_X]--;
	}

	if (currentInputs[SDL_SCANCODE_W])
	{
		inputBus[INPUT_Y]--;
	}

	if (currentInputs[SDL_SCANCODE_S])
	{
		inputBus[INPUT_Y]++;
	}

	if (currentInputs[SDL_SCANCODE_Q])
	{
		inputBus[INPUT_Z]++;
	}

	if (currentInputs[SDL_SCANCODE_E])
	{
		inputBus[INPUT_Z]--;
	}

	if (currentInputs[SDL_SCANCODE_RETURN])
	{
		inputBus[INPUT_QUIT]++;
	}

	for (int i = 0; i < INPUTWIDTH; i++)
		repeatInput[i] = prevInput[i] == inputBus[i];
}

void inputHandler::getUserInputs(__int8 readInputs[INPUTWIDTH])
{
	for (int i = 0; i < INPUTWIDTH; i++)
	{
		readInputs[i] = inputBus[i];
	}
}

void inputHandler::getRepeatInputs(bool readInputs[INPUTWIDTH])
{
	for (int i = 0; i < INPUTWIDTH; i++)
	{
		readInputs[i] = repeatInput[i];
	}
}