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

//event codes used for testing.
//should be located in the "eventType" member of CRE_Event
enum CREEventCode
{
	CRE_EVENT_QUIT,           //0 pushes SDL event to quit game
	CRE_EVENT_TEST_PRINT,     //1 prints a message to the command line. will likely be removes after testing
	CRE_EVENT_ENTITY_MOVE,    //2 moves an entity by data1 in the x dir, data2 in the y dir
	CRE_EVENT_ENTITY_SET_POS  //3 sets an entity's x pos to data1, y pos to data2
};

//Just a bunch of test printing functions.
//will likely be removed after testing.
enum EventPrintType
{
	TEST_0, //0
	TEST_1  //1
};

class eventHandler
{
public:
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

private:
	//i dont even know where im going to put these.
	void moveEntity(const CRE_Event& e);
	void setEntityPos(const CRE_Event& e);

	queue<CRE_Event> CREEventQueue;
};

#endif //EVENT_HPP