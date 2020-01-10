#include "event.h"

extern entity* entityBlock;

queue<CRE_Event> CREEventQueue;

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

void queueEvent(CRE_Event e, unsigned int ID)
{
	e.entityID = ID;
	CREEventQueue.push(e);
}

void passQuitEvent()
{
	SDL_Event e;
	e.type = SDL_QUIT;
}

/* Everything after here is for testing and verification of events and scripts. */
/* Read at the risk fo your own mental health */

// Developer designed event codes:
// This will be in events but this is here for now to 


bool interpretEvents()
{
	CRE_Event e;

	while (!CREEventQueue.empty())
	{
		e = CREEventQueue.front();

		switch (e.eventType)
		{
		case CRE_EVENT_QUIT:
			passQuitEvent();
			return false;

			break;

		case CRE_EVENT_TEST_PRINT:
			switch (e.data1)
			{
			default:
			case TEST_0:
				printf("Test 0\n");
				break;
			case TEST_1:
				printf("Test 1\n");
				break;
			}

			break;

		case CRE_EVENT_ENTITY_MOVE:
			//set pos function

			break;

		case CRE_EVENT_ENTITY_ABS_MOVE:
			//absolute set pos function

			break;

		default:
			printf("Unknown event code: %i. Skipping event.\nPlease refer to ", e.eventType);
			break;
		}
	}

	return true;
}