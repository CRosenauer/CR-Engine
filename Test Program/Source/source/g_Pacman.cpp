#include "g_Pacman.h"

#include "../entityHandler.h"
#include "../input.h"
#include "../audio.h"
#include "../video.h"
#include "../eventHandler.h"

#include "s_gameState.h"
#include "s_Collision.h"
#include "e_Pacman.h"
#include "s_kinematics.h"
#include "s_Tiling.h"
#include "e_ImgChar.h"
#include "ev_Pacman.h"

extern CRE_InputHandler CREInput;
extern CRE_Audio        CREAudio;
extern CRE_Video		CREVideo;
extern CRE_EventHandler CREEventHandler;

namespace
{
	static CRE_Entity* pacman = allocateEntityPtr(PACMAN);

	bool initialized = false;

	void init()
	{
		pacman->setTexture(e_Pacman::imageDat::pacmanSprite);
		s_Tiling::loadMap();
	}

	imageString* testImgStr = NULL;
}

void g_Pacman()
{
	if (!initialized)
	{
		init();
	}

	if (testImgStr == NULL)
	{
		testImgStr = new imageString;
	}

	{
		char buffer[32];
		sprintf_s(buffer, "FPS: %.2f\n", CREVideo.getFrameRate());

		testImgStr->loadString(buffer);
	}

	switch (s_gameState::getPauseState())
	{
	default:
	case s_gameState::GAMEPLAY:

		CREEventHandler.queueEvent(ev_Pacman::ev_checkPause);
		CREEventHandler.queueEvent(ev_Pacman::ev_movePacman, pacman->getEntityID());

		break;

	case s_gameState::MENU:

		CREEventHandler.queueEvent(ev_Pacman::ev_checkPause);
		
		break;
	}

	sortEntities();
}