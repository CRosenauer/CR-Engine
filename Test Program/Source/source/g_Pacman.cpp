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

	static CRE_Entity* pacman = entityFromID(allocateEntity(PACMAN));

	static GameState gameState = GAMEPLAY;

	static __int8 inputs[INPUTWIDTH] = {0, 0, 0};
	static bool   repInputs[INPUTWIDTH] = { false, false, false };

	static bool collision[4] = { false, false, false, false };

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

		//interprent inputs and check collision
		s_Collision::checkCollision(pacman->getEntityID(), s_Tiling::gameMap, collision);

		if (inputs[INPUT_Y] < 0)
		{
			if (!collision[s_Collision::UP])
				e_Pacman::logic::moveUp(pacman->getEntityID());
				
		}
		else if(inputs[INPUT_Y] > 0)
		{
			if (!collision[s_Collision::DOWN])
				e_Pacman::logic::moveDown(pacman->getEntityID());
		}

		if (inputs[INPUT_X] < 0)
		{
			if (!collision[s_Collision::LEFT])
				e_Pacman::logic::moveLeft(pacman->getEntityID());
		}
		else if (inputs[INPUT_X] > 0)
		{
			if (!collision[s_Collision::RIGHT])
				e_Pacman::logic::moveRight(pacman->getEntityID());
		}


		//update pacman movement
		s_Kinematics::updateKinematics(pacman->getEntityID());

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
}