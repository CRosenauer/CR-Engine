#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL_events.h>
#include <queue>
#include "entity.h"

//CRE Events are altered and simplified versions of SDL's internal event strucuts.
//This change was made to have an easier to use type of event thats still compatible with
//SDL Events.
//CRE Events were made so I didn't need to deal with void pointers in SDL_UserEvents
//and I feel that giving events access to all entities is a cleaner way to update a game
//compared to having a virtual update function in a child class of entity.

//struct to hold CRE event data.
//Note that this is basically a rip off of SDL_UserEvent without information that
//goes unused is not included.
struct CRE_Event
{
	int eventType;
	int data1;
	int data2;

	unsigned int entityID;
};

//converts CRE_Event to an SDL_Event
//copies over data from CRE_Event to SDL_UserEvent member of SDL_Event
SDL_Event convertCREtoSDL(const CRE_Event& event);

//converts SDL_Event to an CRE_Event
//copies over data from SDL_UserEvent member of SDL_Event to CRE_Event 

//frees the dynamic memory portion of user part of the passed SDL_Event*
void freeSDLUserEvent(SDL_Event* e);

//queues event with the given target entity ID
//passed ID is applied to a copy of the passed event
//event is pushed onto the internal event queue
void queueEvent(CRE_Event e, unsigned int ID);

//cycles through and interprets every event in the event queue
//unless a quit event is found
//if a quit event is found function returns false, else returns true
//cycles through each event applying the correct logic to the entity ID
//specified within the event.
bool interpretEvents();

//event codes used for testing.
//should be located in the "eventType" member of CRE_Event
enum CREEventCode
{
	CRE_EVENT_QUIT,           //0 
	CRE_EVENT_TEST_PRINT,     //1
	CRE_EVENT_ENTITY_MOVE,    //2
	CRE_EVENT_ENTITY_ABS_MOVE //3
};

//
enum EventPrintType
{
	TEST_0, //0
	TEST_1  //1
};

#endif //EVENT_HPP