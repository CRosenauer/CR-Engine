#include "event.h"

SDL_Event convertCREtoSDL(const CRE_Event& event)
{
	SDL_Event e;
	e.type = SDL_USEREVENT;
	e.user.type      = NULL;
	e.user.timestamp = NULL;
	e.user.windowID  = NULL;
	e.user.code      = event.eventType;

	int* tempData1 = new int;
	*tempData1 = event.data1;

	int* tempData2 = new int;
	*tempData2 = event.data2;

	e.user.data1 = tempData1;
	e.user.data2 = tempData2;

	return e;
}

void freeSDLUserEvent(SDL_Event* e)
{
	delete e->user.data1;
	delete e->user.data2;
}

void SDL_PushEvent(CRE_Event* e)
{
	SDL_Event event = convertCREtoSDL(*e);
	SDL_PushEvent(&event);
}

const int NUMBER_OF_USER_EVENTS = 2;