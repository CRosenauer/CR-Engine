#include "TestGame.h"



#define TEST_SCRIPT

//Buses to hold user inputs, and entities respectively
extern __int8* inputBus;
extern entity* entityBlock;

//Handlers for input and video.
extern audio         CREAudio;
extern scriptHandler CREScript;

entity* Player;



const SDL_Rect UNDEFINED_RECT = { -1, -1, -1, -1 };

enum GAME_SCREEN
{
	NOT_INITIALIZED,
	INITIALIZED
};

void TestGame()
{	
	/* General overview of game loop:
	 *
	 * interpret inputs
	 * loop reading and writing events
	 * handle read events, update entities etc
	 * 
	 * read scripts
	 * post script events
	 * update script events
	 * exit
	 *
	 * exit at anypoint a quit command is given
	*/

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
		Player = &entityBlock[0];
		Player->define();
		entityBlock[1].define();

		CREAudio.loadMusic("Friday_Chinatown.mp3");

		Player->setTexture("ship.png", tempSource, 8, 8);
		Player->setPosition(32, 32, 0); 

		entityBlock[1].setAnimation(&testAnimation00, ANIMATION_LOOP);
		entityBlock[1].setPosition(128, 128, 0);

		CREScript.loadScript(testScript00, Player->getEntityID());

#ifdef TEST_SCRIPT


		//pass script to CREScript
#endif
		gameScreen = INITIALIZED;
		break;
	case INITIALIZED:
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