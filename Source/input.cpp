#include "input.h"

inputHandler::inputHandler()
{
	//To implement: load keymap from file.

	for (int i = 0; i < INPUTWIDTH; i++)
		inputBus[i] = 0;
}

void inputHandler::pollInputs()
{
	for (int i = 0; i < INPUTWIDTH; i++)
		inputBus[i] = 0;

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

	if (currentInputs[SDL_SCANCODE_RETURN])
	{
		inputBus[INPUT_QUIT]++;
	}
}

void inputHandler::getUserInputs(__int8 readInputs[INPUTWIDTH])
{
	for (int i = 0; i < INPUTWIDTH; i++)
	{
		readInputs[i] = inputBus[i];
	}
}