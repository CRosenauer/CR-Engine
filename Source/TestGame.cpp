#include "TestGame.h"

//Buses to hold user inputs, and entities respectively
__int8* input;
entity* entityBus;

//Handlers for input and video.
video* Video;
audio* Audio;

entity PlayerEntity;

enum GAME_SCREEN
{
	NOT_INITIALIZED,
	INITIALIZED
};

const SDL_Rect UNDEFINED_RECT = { -1, -1, -1, -1 };

void gameLogicInit(__int8*& inputB, entity*& entityB, video* video, audio* audio)
{
	input = inputB;
	entityBus = entityB;
	Video = video;
	Audio = audio;
}

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
	SDL_Rect tempDest;
	tempDest.x = 0;
	tempDest.y = 0;
	tempDest.w = 16;
	tempDest.h = 16;
	int tempPos[3];

	switch (gameScreen)
	{
	default:
	case NOT_INITIALIZED:
		Audio->loadMusic("Friday_Chinatown.mp3");
		entityBus[0].setTexture("ship.png", tempSource, tempDest, 8, 8);
		entityBus[0].setPosition(32, 32, 0);

		Video->loadTexture(entityBus[0].getTexture(), CRE_V_TEXTURE_SPRITE);
		gameScreen = INITIALIZED;
		break;
	case INITIALIZED:
		entityBus[0].getPosition(tempPos);
		if (tempPos[0] < 100)
			tempPos[0]++;
		else if (tempPos[0] >= 100 && tempPos[1] < 100)
			tempPos[1]++;
		else if (tempPos[0] < 0 && tempPos[1] >= 100)
			tempPos[0]--;
		else
			tempPos[1]--;
		entityBus[0].setPosition(tempPos[0], tempPos[1], tempPos[2]);
		Video->loadTexture(entityBus[0].getTexture(), CRE_V_TEXTURE_SPRITE);
		break;
	}

	if (input[2] == 1)
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}
}