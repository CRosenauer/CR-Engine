#include "TestGame.h"

//Buses to hold user inputs, and entities respectively
extern __int8* inputBus;
extern vector<entity*> entityBlock;

//Handler for audio.
extern audio CREAudio;

//handler for scripts
extern scriptHandler CREScript;


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
	int tempPos[3];

	switch (gameScreen)
	{
	default:
	case NOT_INITIALIZED:
		
		entityBlock.push_back(Player);
		
		entityBlock.push_back(testEntity);

		CREAudio.loadMusic("Friday_Chinatown.mp3");

		Player->setTexture("ship.png", tempSource, 8, 8);
		Player->setPosition(32, 32, 0); 

		entityBlock[1]->setAnimation(&testAnimation00, ANIMATION_LOOP);
		entityBlock[1]->setPosition(128, 128, 0);

		gameScreen = INITIALIZED;
		break;
	case INITIALIZED:
		if(Player != NULL)
			Player->getPosition(tempPos);

		if (inputBus[0] > 0)
			tempPos[0]++;
		else if (inputBus[0] < 0)
			tempPos[0]--;
			
		if (inputBus[1] > 0)
			tempPos[1]++;
		else if (inputBus[1] < 0)
			tempPos[1]--;
			
		Player->setPosition(tempPos[0], tempPos[1], tempPos[2]);

		break;
	}

	if (inputBus[2] == 1)
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}
}