#include "script.h"

void scriptHandler::loadScript(script eScript, unsigned int ID)
{
	//script is pushed to the front of the list
	//order of this list doesn't really matter
	scriptList.push_front(eScript);
	scriptIndex = scriptList.begin();

	if (ID != NULL)
		scriptIndex->entityID = ID;

	//wait we need something more here.

	//pushes iterator of the added script list to event queue
	//the iterator is used to edit the value of the script
	pushEvent(scriptIndex);
}

void scriptHandler::pushEvent(const std::list<script>::iterator& scriptLoc)
{
	//pushes event to SDL event queue
	//Note: I don't know if this will work or not as im passing a stack
	//memory value as a pointer.
	//according to SDL documentation this should work but well see.
	SDL_Event e;

	e = convertCREtoSDL(scriptLoc->event);

	SDL_PushEvent(&e);
}

void scriptHandler::proccessScripts()
{
	//traverses script list
	for (scriptIndex = scriptList.begin(); scriptIndex != scriptList.end(); scriptIndex++)
	{
		//if frameCount of a given script == 0 (script last for 0 frames (instant) or script has passed its delay)
		while (scriptIndex->frameCount == 0)
		{
			//if there is no next event to push in the script
			if (scriptIndex->nextScript == NULL)
			{
				//
				scriptIndex = scriptList.erase(scriptIndex);
				scriptIndex--;
				break;
			}
			else
			{
				//sets script to next script and pushes the next script to event queue.
				int ID = scriptIndex->entityID;

				*scriptIndex = *(scriptIndex->nextScript);
				scriptIndex->entityID = ID;

				pushEvent(scriptIndex);
			}
		}

		//reduces the number of frames the script delays before continuing by 1.
		(scriptIndex->frameCount)--;
	}
}