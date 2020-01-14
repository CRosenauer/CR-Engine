#include "input.h"

inputHandler::inputHandler()
{
	//load keymap from file.

	inputBus = NULL;

	printf("CREngine Warning: inputHandler default constructor called. For initialization usage only.\n");
}

inputHandler::inputHandler (short inputSize)
{
	numberOfInputs = inputSize;
}

void inputHandler::pollInputs()
{
	for (int i = 0; i < numberOfInputs; i++)
		inputBus[i] = 0;

	if (currentInputs[SDL_SCANCODE_W])
	{
		inputBus[1]--;
	}

	if (currentInputs[SDL_SCANCODE_S])
	{
		inputBus[1]++;
	}

	if (currentInputs[SDL_SCANCODE_D])
	{
		inputBus[0]++;
	}

	if (currentInputs[SDL_SCANCODE_A])
	{
		inputBus[0]--;
	}

	if (currentInputs[SDL_SCANCODE_RETURN])
	{
		inputBus[2]++;
	}
}

