#include "input.h"

namespace eng_Input
{
	__int8 inputBus[INPUTWIDTH];

	bool repeatInput[INPUTWIDTH];
}

CRE_InputHandler::CRE_InputHandler()
{
	//To implement: load keymap from file.

	for (int i = 0; i < INPUTWIDTH; i++)
	{
		eng_Input::inputBus[i] = 0;
		eng_Input::repeatInput[i] = false;
	}
		
}

void CRE_InputHandler::pollInputs()
{
	SDL_PumpEvents();
	currentInputs = SDL_GetKeyboardState(NULL);

	__int8 prevInput[INPUTWIDTH];

	for (int i = 0; i < INPUTWIDTH; i++)
	{
		prevInput[i] = eng_Input::inputBus[i];
		eng_Input::inputBus[i] = 0;
	}
		

	if (currentInputs[SDL_SCANCODE_D])
	{
		eng_Input::inputBus[INPUT_X]++;
	}

	if (currentInputs[SDL_SCANCODE_A])
	{
		eng_Input::inputBus[INPUT_X]--;
	}

	if (currentInputs[SDL_SCANCODE_W])
	{
		eng_Input::inputBus[INPUT_Y]--;
	}

	if (currentInputs[SDL_SCANCODE_S])
	{
		eng_Input::inputBus[INPUT_Y]++;
	}

	if (currentInputs[SDL_SCANCODE_RETURN])
	{
		eng_Input::inputBus[INPUT_ENTER]++;
	}

	for (int i = 0; i < INPUTWIDTH; i++)
		eng_Input::repeatInput[i] = prevInput[i] == eng_Input::inputBus[i];
}

void CRE_InputHandler::getUserInputs(__int8 readInputs[INPUTWIDTH])
{
	for (int i = 0; i < INPUTWIDTH; i++)
	{
		readInputs[i] = eng_Input::inputBus[i];
	}
}

void CRE_InputHandler::getRepeatInputs(bool readInputs[INPUTWIDTH])
{
	for (int i = 0; i < INPUTWIDTH; i++)
	{
		readInputs[i] = eng_Input::repeatInput[i];
	}
}