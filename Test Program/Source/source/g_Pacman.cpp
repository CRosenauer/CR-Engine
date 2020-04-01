#include "g_Pacman.h"

#include "../entityHandler.h"
#include "../input.h"
#include "../audio.h"

#include "s_Collision.h"
#include "e_Pacman.h"
#include "s_kinematics.h"
#include "s_Tiling.h"

extern CRE_InputHandler CREInput;
extern CRE_Audio        CREAudio;

namespace
{
	enum GameState
	{
		GAMEPLAY,
		MENU
	};

	static CRE_Entity* pacman = allocateEntityPtr(PACMAN);

	static GameState gameState = GAMEPLAY;

	static __int8 inputs[INPUTWIDTH] = {0, 0, 0};
	static bool   repInputs[INPUTWIDTH] = { false, false, false };

	static  e_Pacman::enums::direction dir = e_Pacman::enums::DOWN;

	bool initialized = false;

	void init()
	{
		pacman->setTexture(e_Pacman::imageDat::pacmanSprite);
	}
}

void g_Pacman()
{
	//retrieve inputs
	CREInput.getUserInputs(inputs);
	CREInput.getRepeatInputs(repInputs);

	if (!initialized)
	{
		init();
	}

	switch (gameState)
	{
	default:
	case GAMEPLAY:

		s_Tiling::loadMap();

		if (inputs[INPUT_ENTER] && !repInputs[INPUT_ENTER])
		{
			gameState = MENU;
			CREAudio.loadSFX("shine.wav");
			break;
		}


		if (inputs[INPUT_Y] < 0)
		{
			dir = e_Pacman::enums::UP;
		}
		else if(inputs[INPUT_Y] > 0)
		{
			dir = e_Pacman::enums::DOWN;
		}

		if (inputs[INPUT_X] < 0)
		{
			dir = e_Pacman::enums::LEFT;
		}
		else if (inputs[INPUT_X] > 0)
		{
			dir = e_Pacman::enums::RIGHT;
		}

		//update pacman movement
		s_Collision::moveEntity(pacman->getEntityID(), dir);

		break;

	case MENU:

		s_Tiling::unloadMap();

		if (inputs[INPUT_ENTER] && !repInputs[INPUT_ENTER])
		{
			gameState = GAMEPLAY;
		}

		//check for enter
		break;
	}

	sortEntities();
}