#include "TestGame.h"

//Buses to hold user inputs, and entities respectively
static __int8* input = NULL;
static entity* entityBus = NULL;

//Handlers for input and video.
static video* Video;
static audio* Audio;

entity PlayerEntity;

enum GAME_SCREEN
{
	NO_MUSIC_LOADED,
	MUSIC_LOADED
};



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
		gameScreen = NO_MUSIC_LOADED;
	}
		

	switch (gameScreen)
	{
	default:
	case NO_MUSIC_LOADED:
		Audio->loadMusic("Friday_Chinatown.mp3");
		Audio->loadSFX("Shine.wav");
		gameScreen = MUSIC_LOADED;
		break;
	case MUSIC_LOADED:
		break;
	}

	if (input[2] == 1)
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}
}