#include "TestGame.h"

//Buses to hold entities
extern vector<entity*> entityBlock;

//handlers for audio, inputs, etc. Most externally defined in CREngine.cpp
extern audio        CREAudio;
extern inputHandler CREInput;

extern scriptHandler CREScriptHandler;
extern eventHandler  CREEventHandler;


const SDL_Rect UNDEFINED_RECT = { -1, -1, -1, -1 };

enum GAME_SCREEN
{
	NOT_INITIALIZED,
	INITIALIZED
};

entity* Player;

void TestGame()
{	
	static GAME_SCREEN gameScreen;
	
	if (gameScreen == NULL)
	{
		gameScreen = NOT_INITIALIZED;
	}
	
	SDL_Rect tempSource;
	tempSource.x = 0;
	tempSource.y = 0;
	tempSource.w = 16;
	tempSource.h = 16;
	__int8 userInputs[INPUTWIDTH];
	bool repeatedInputs[INPUTWIDTH];
	int tempPos[3] = {0, 0, 0};

	switch (gameScreen)
	{
	default:
	case NOT_INITIALIZED:

		Player = entityFromID(allocateEntity(test));

		CREScriptHandler.loadScript( testScript00, Player->getEntityID() );

		gameScreen = INITIALIZED;
		break;
		
	case INITIALIZED:
		if(Player != NULL)
			Player->getPosition(tempPos);

		CREInput.getUserInputs(userInputs);
		CREInput.getRepeatInputs(repeatedInputs);

		//x co-ord inputs (A/D)
		if (userInputs[INPUT_X] > 0)
			tempPos[0]++;
		else if (userInputs[INPUT_X] < 0)
			tempPos[0]--;
		
		//y co-ord inputs (W/S)
		if (userInputs[INPUT_Y] > 0)
			tempPos[1]++;
		else if (userInputs[INPUT_Y] < 0)
			tempPos[1]--;
		
		//z co-ord inputs (Q/E)
		if (userInputs[INPUT_Z] > 0 && !repeatedInputs[INPUT_Z])
			tempPos[2]++;
		else if(userInputs[INPUT_Z] < 0 && !repeatedInputs[INPUT_Z])
			tempPos[2]--;

		//quit inputs (enter)
		if (userInputs[INPUT_QUIT] == 1)
		{
			CREEventHandler.passQuitEvent();
		}

		Player->setPosition(tempPos[0], tempPos[1], tempPos[2]);

		break;
	}
}