#ifndef EV_PACMAN_H
#define EV_PACMAN_H

#include "../event.h"

#include "s_Collision.h"

namespace ev_Functions
{
	void movePacman(CRE_Entity* entity, void* unused);

	void checkPause(CRE_Entity* unused1, void* unused2);
}

namespace ev_Pacman
{
	//when passed event checks inputs and moves pacman acordingly
	const CRE_Event ev_movePacman =
	{
		CRE_EVENT_FUNCTION,

		{ (void*) ev_Functions::movePacman },
		{ NULL },
		{ NULL },
		{ NULL }
	};

	//when passed event checks inputs and pauses/unpauses game
	const CRE_Event ev_checkPause =
	{
		CRE_EVENT_FUNCTION,

		{ (void*) ev_Functions::checkPause },
		{ NULL },
		{ NULL },
		{ NULL }
	};
}

#endif //EV_PACMAN_H