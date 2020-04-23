#ifndef S_GAMESTATE_H
#define S_GAMESTATE_H


namespace s_gameState
{
	enum gameState
	{
		GAMEPLAY,
		MENU
	};

	gameState getPauseState();
	void setPauseState(gameState gs);
}

#endif //S_GAMESTATE_H