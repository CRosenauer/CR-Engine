#include "TestGame.h"

//Buses to hold entities
extern vector<entity*> entityBlock;

//handlers for audio, inputs, etc. Most externally defined in CREngine.cpp
extern audio CREAudio;
extern scriptHandler CREScript;
extern inputHandler CREInput;


const SDL_Rect UNDEFINED_RECT = { -1, -1, -1, -1 };

enum GAME_SCREEN
{
	NOT_INITIALIZED,
	INITIALIZED
};

entity* Player = new entity;
entity* testEntity = new entity;

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
	int tempPos[3] = {0, 0, 0};

	switch (gameScreen)
	{
	default:
	case NOT_INITIALIZED:
		
		entityBlock.push_back(Player);
		
		entityBlock.push_back(testEntity);

		CREAudio.loadMusic("Friday_Chinatown.mp3");

		Player->setTexture(ship);
		Player->setPosition(32, 32, 0); 

		testEntity->setAnimation(&testAnimation00, ANIMATION_LOOP);
		testEntity->setPosition(128, 128, 0);

		gameScreen = INITIALIZED;
		break;
		
	case INITIALIZED:
		if(Player != NULL)
			Player->getPosition(tempPos);

		CREInput.getUserInputs(userInputs);

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
		
		//quit inputs (enter)
		if (userInputs[INPUT_QUIT] == 1)
		{
			SDL_Event e;
			e.type = SDL_QUIT;
			SDL_PushEvent(&e);
		}

		Player->setPosition(tempPos[0], tempPos[1], tempPos[2]);
		
		break;
	}
}