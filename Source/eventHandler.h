#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL_events.h>

#include <vector>
#include <queue>

#include "config.h"

#include "event.h"
#include "script.h"

#include "video.h"
#include "audio.h"
#include "entityHandler.h"
#include "ground.h"


class eventHandler
{
public:
	//queues event with the given target entity ID
	//passed ID is applied to a copy of the passed event
	//event is pushed onto the internal event queue
	void queueEvent(CRE_Event e, unsigned int ID);

	//same as previous but assumes entityID is unused
	//or entityID is already included in CRE_Event struct.
	void queueEvent(CRE_Event e);

	//cycles through and interprets every event in the event queue
	//unless a quit event is found
	//if a quit event is found function returns false, else returns true
	//cycles through each event applying the correct logic to the entity ID
	//specified within the event.
	bool processEvents();

	//passes quit event to event queue for exitting the game.
	void passQuitEvent();

private:

	//loads all events from primitive event queue.
	void queuePrimitiveEvents();

	queue<CRE_Event> CREEventQueue;
};



#endif