#include "input.h"

inputHandler::inputHandler()
{
	//load keymap from file.

	inputBus = NULL;

	printf("CREngine Warning: inputHandler default constructor called. For initialization usage only.\n");
}

inputHandler::inputHandler (short inputSize, __int8*& input)
{
	numberOfInputs = inputSize;
	inputBus = input;
}

void inputHandler::pollInputs()
{
	for (int i = 0; i < numberOfInputs; i++)
		inputBus[i] = 0;

	while (SDL_PollEvent(&e) != 0)
	{
        if(e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				inputBus[0]++;
				break;
			case SDLK_s:
				inputBus[0]--;
				break;
			case SDLK_d:
				inputBus[1]++;
				break;
			case SDLK_a:
				inputBus[1]--;
				break;
			case SDLK_RETURN:
				inputBus[2]++;
				break;
			default:
				break;
			}
		}
	}
}

