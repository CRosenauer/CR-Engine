#ifndef SCRIPT_H
#define SCRIPT_H

#include <queue>

#include "config.h"

#include "event.h"


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

struct CRE_Script
{
	CRE_Event event;
	int frameCount;
	unsigned int entityID;

	const CRE_Script* nextScript;
};

typedef CRE_Script* CRE_ScriptPtr;

#endif //SCRIPT_H