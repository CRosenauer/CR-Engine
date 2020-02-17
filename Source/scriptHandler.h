#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <list>

#include "script.h"
#include "event.h"
#include "eventHandler.h"

// class to handle reading, storing and interpreting events/updates from scripts.
class scriptHandler
{
public:

	//loads a script into the linked list and pushes the event located in the script
	void loadScript(script eScript, unsigned int ID);

	//goes through every script stored in the current scriptList
	//advances the frame count of each script
	//when a script frame count reaches 0 the next script is loaded and its event is pushed.
	void processScripts();

private:
	//linked list that holds copies of scripts stored in rom
	std::list<script> scriptList;

	//iterator used to access and traverse scriptList.
	std::list<script>::iterator scriptIndex;

	//pushes an event to event queue.
	//event queue is not stored in "script.h" but is part of SDL.
	void pushEvent(const std::list<script>::iterator& scriptLoc);
};

#endif //SCRIPTHANDLER_H
