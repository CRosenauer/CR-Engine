#include "input.h"

inputHandler::inputHandler()
{
	//load keymap from file.

	if (inputBus == NULL)
	{
		//allocate inputBus
		try
		{
			printf("Stub: Initializing 3 inputs on inputBus");
			inputBus = new __int8[INPUTWIDTH];
		}
		catch (std::bad_alloc)
		{
			printf("CREngine init error. Failed to initialize inputBus. Exiting program\n");
			exit(1);
		}
	}
}

inputHandler::~inputHandler()
{
	//deallocate inputBus from memory
	delete[] inputBus;
}


void inputHandler::pollInputs()
{
	for (int i = 0; i < INPUTWIDTH; i++)
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

