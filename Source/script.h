#ifndef SCRIPT_H
#define SCRIPT_H

#include "event.h"
#include <list>

// Developer designed event codes:
// This will be in events but this is here for now to 

#define CRE_EVENTTYPE_QUIT        0
#define CRE_EVENTTYPE_TEST_PRINT  1
#define CRE_EVENTTYPE_ENTITY_MOVE 2

// Struct used to hold script frames for scripting functionality
// stricpts work very similar to animations and by extension, linked lists
// 
// Members:
// SDL_Event event:
// This member dictates what event will occur when the script is accesses
// 
// int frameCount:
// This member determines the number of frames between activating the current
// event in the script and the next event in the script.
// a frameCount of 0 will have the event play one after another
//
// unsigned int entityID:
// This member is used to determine which entity the event will take effect on
// if any.
//
// script* nextScript:
// Finally, nextScript is a pointer to the next event to take place.

struct script
{
	CRE_Event event;
	int frameCount;
	unsigned int entityID;

	const script* nextScript;
};

typedef script* scriptPtr;

// class to handle reading, storing and interpreting events/updates from scripts.
class scriptHandler
{
public:

	//loads a script into the linked list and pushes the event located in the script
	void loadScript(script eScript, unsigned int ID);

	//goes through every script stored in the current scriptList
	//advances the frame count of each script
	//when a script frame count reaches 0 the next script is loaded and its event is pushed.
	void proccessScripts();

private:
	//linked list that holds copies of scripts stored in rom
	std::list<script> scriptList;

	//iterator used to access and traverse scriptList.
	std::list<script>::iterator scriptIndex;

	//pushes an event to event queue.
	//event queue is not stored in "script.h" but is part of SDL.
	void pushEvent(const std::list<script>::iterator& scriptLoc);
};

#endif //SCRIPT_H