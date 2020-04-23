#include "ev_Pacman.h"

#include "../input.h"
#include "s_gameState.h"

extern CRE_InputHandler CREInput;
extern CRE_Audio		CREAudio;

namespace ev_Functions
{
	static __int8 userInputs[INPUTWIDTH];
	static bool   repInputs[INPUTWIDTH];

	static  e_Pacman::enums::direction dir = e_Pacman::enums::NONE;

	void movePacman(CRE_Entity* entity, void* unused)
	{
		if (s_gameState::getPauseState() == s_gameState::MENU)
			return;

		//get inputs
		CREInput.getUserInputs(userInputs);
		CREInput.getRepeatInputs(repInputs);

		//check inputs for direction
		if (userInputs[INPUT_Y] < 0)
		{
			dir = e_Pacman::enums::UP;
		}
		else if (userInputs[INPUT_Y] > 0)
		{
			dir = e_Pacman::enums::DOWN;
		}

		if (userInputs[INPUT_X] < 0)
		{
			dir = e_Pacman::enums::LEFT;
		}
		else if (userInputs[INPUT_X] > 0)
		{
			dir = e_Pacman::enums::RIGHT;
		}

		//update pacman movement
		s_Collision::moveEntity(entity->getEntityID(), dir);
	}

	void checkPause(CRE_Entity* unused1, void* unused2)
	{
		CREInput.getUserInputs(userInputs);
		CREInput.getRepeatInputs(repInputs);

		if (userInputs[INPUT_ENTER] && !repInputs[INPUT_ENTER])
		{
			if (s_gameState::getPauseState() == s_gameState::GAMEPLAY)
			{
				s_gameState::setPauseState(s_gameState::MENU);
				CREAudio.loadSFX("shine.wav");
				s_Tiling::unloadMap();
			}
			else
			{
				s_gameState::setPauseState(s_gameState::GAMEPLAY);
				s_Tiling::loadMap();
			}
		}
	}
}
