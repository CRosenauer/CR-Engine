#include "s_gameState.h"

static s_gameState::gameState pauseState;


namespace s_gameState
{
	gameState getPauseState()
	{
		return pauseState;
	}

	void setPauseState(gameState gs)
	{
		pauseState = gs;
	}
}