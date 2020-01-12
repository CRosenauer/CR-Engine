#include "event.h"

extern entity* entityBlock;

void eventHandler::queueEvent(CRE_Event e, unsigned int ID)
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

//developer helper functions
//not included in event.h because these functions will likely sit in other files
//in an actual game.

void eventHandler::moveEntity(const CRE_Event& e)
{
	int tempPosArray[3];

	//********************************hard coded value, change later
	for (int i = 0; i < 64; i++)
	{
		if (entityBlock[i].getEntityID() == e.entityID)
		{
			entityBlock[i].getPosition(tempPosArray);

			tempPosArray[0] += e.data1;
			tempPosArray[1] += e.data2;

			entityBlock[i].setPosition(tempPosArray[0], tempPosArray[1], tempPosArray[2]);

			break;
		}
	}
}

void eventHandler::setEntityPos(const CRE_Event& e)
{
	int tempPosArray[3];

	//********************************hard coded value, change later
	for (int i = 0; i < 64; i++)
	{
		if (entityBlock[i].getEntityID() == e.entityID)
		{
			entityBlock[i].getPosition(tempPosArray);

			tempPosArray[0] = e.data1;
			tempPosArray[1] = e.data2;

			entityBlock[i].setPosition(tempPosArray[0], tempPosArray[1], tempPosArray[2]);

			break;
		}
	}
}

bool eventHandler::interpretEvents()
{
	CRE_Event e;

	while (!CREEventQueue.empty())
	{
		e = CREEventQueue.front();
		CREEventQueue.pop();

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
			moveEntity(e);
			break;

		case CRE_EVENT_ENTITY_SET_POS:
			setEntityPos(e);
			break;

		default:
			printf("Unknown event code: %i. Skipping event.\nPlease refer to event.h, enum CREEventCode\n", e.eventType);
			break;
		}
	}

	return true;
}