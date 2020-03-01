#include "TestGame.h"

//Buses to hold entities
extern vector<CRE_Entity*> entityBlock;

//handlers for audio, inputs, etc. Most externally defined in CREngine.cpp
extern CRE_Video		CREVideo;
extern CRE_Audio        CREAudio;
extern CRE_InputHandler CREInput;

extern CRE_ScriptHandler CREScriptHandler;
extern CRE_EventHandler  CREEventHandler;


const SDL_Rect UNDEFINED_RECT = { -1, -1, -1, -1 };

enum GAME_SCREEN
{
	NOT_INITIALIZED,
	INITIALIZED
};

CRE_Entity* Player;
static GAME_SCREEN gameScreen = NOT_INITIALIZED;

void TestGame()
{	
	static Uint8 alpha = 255;

	SDL_Rect tempSource;
	tempSource.x = 0;
	tempSource.y = 0;
	tempSource.w = 16;
	tempSource.h = 16;
	__int8 userInputs[INPUTWIDTH];
	bool repeatedInputs[INPUTWIDTH];
	int tempPos[3] = {0, 0, 0};
	int cameraPos[2] = {32, 32};
	static float xScale = 1;
	static float yScale = 1;

	switch (gameScreen)
	{
	default:
	case NOT_INITIALIZED:

		Player = entityFromID(allocateEntity(test));

		CREScriptHandler.loadScript(testScript00, Player->getEntityID());

		Player->setPosition(31, 31, 0);

		CREVideo.setCameraPos(cameraPos);


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
		if (userInputs[INPUT_Z] > 0)
		{
			if (xScale > 0.25)
			{
				xScale -= 0.125;
				Player->setXScale(xScale);
			}

			if (yScale > 0.25)
			{
				yScale -= 0.125;
				Player->setYScale(yScale);
			}
			
			//printf("Scaleing:\nx: %f\ny: %f\n\n", xScale, yScale);
		}
		else if (userInputs[INPUT_Z] < 0)
		{
			xScale += 0.125;
			yScale += 0.125;
			Player->setXScale(xScale);
			Player->setYScale(yScale);
			//printf("Scaleing:\nx: %f\ny: %f\n\n", xScale, yScale);
		}

		//quit inputs (enter)
		if (userInputs[INPUT_QUIT] == 1)
		{
			CREEventHandler.passQuitEvent();
		}

		Player->setPosition(tempPos[0], tempPos[1], tempPos[2]);
		
		Player->addRotationDegree(10);

		//CREVideo.getCameraPos(cameraPos);

		//checks for updating camera position
		
		//check x position
		/*
		if (tempPos[0] - cameraPos[0] < 200 )
		{
			cameraPos[0] = tempPos[0] - 200;
		}
		else if ( cameraPos[0] + 640 - tempPos[0] < 200)
		{
			cameraPos[0] = tempPos[0] + 200 - 640;
		}

		//check y position
		if (tempPos[1] - cameraPos[1] < 200)
		{
			cameraPos[1] = tempPos[1] - 200;
		}
		else if (cameraPos[1] + 480 - tempPos[1] < 200)
		{
			cameraPos[1] = tempPos[1] + 200 - 480;
		}

		CREVideo.setCameraPos(cameraPos);
		*/

		break;
	}
}