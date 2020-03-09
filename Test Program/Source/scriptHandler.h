#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <list>

#include "config.h"

#include "script.h"
#include "event.h"
#include "eventHandler.h"

// class to handle reading, storing and interpreting events/updates from scripts.
class CRE_ScriptHandler
{
public:

	//loads a script into the linked list and pushes the event located in the script
	void loadScript(CRE_Script eScript, unsigned int ID);

	//goes through every script stored in the current scriptList
	//advances the frame count of each script
	//when a script frame count reaches 0 the next script is loaded and its event is pushed.
	void processScripts();

private:
	//linked list that holds copies of scripts stored in rom
	std::list<CRE_Script> scriptList;

	//iterator used to access and traverse scriptList.
	std::list<CRE_Script>::iterator scriptIndex;

	//pushes an event to event queue.
	//event queue is not stored in "script.h" but is part of SDL.
	void pushEvent(const std::list<CRE_Script>::iterator& scriptLoc);

	//performs operations on "goto" type events that would normally occur in eventHandler class.
	//function needed to process goto event when they are loaded rather than after scriptes are loaded.
	void processGotoEvent(CRE_Script s);
};

#endif //SCRIPTHANDLER_H
