#include "scriptHandler.h"

extern queue<script>    primitiveScriptQueue;
extern queue<CRE_Event> primitiveEventQueue;

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
	scriptLoc->event.entityID = scriptLoc->entityID;
	primitiveEventQueue.push(scriptLoc->event);
}

//broken function
//the iterator gets unhappy when i start changing things and deleting things
//theres also a memory leak. maybe not in this function but somewhere
void scriptHandler::processScripts()
{
	//traverses script list and processes each event in the script list.
	for (scriptIndex = scriptList.begin(); scriptIndex != scriptList.end(); scriptIndex++)
	{
		bool scriptDeleted = false;

		//if frameCount of a given script == 0 (script last for 0 frames (instant) or script has passed its delay)
		while (scriptIndex->frameCount == 0)
		{
			//if there is no next event to push in the script
			if (scriptIndex->nextScript == NULL)
			{
				//erases complete script from memory
				scriptIndex = scriptList.erase(scriptIndex);

				if (!scriptList.empty())
					scriptIndex--;

				scriptDeleted = true;

				break;
			}
			else
			{
				//sets script to next script and pushes the next script to event queue.
				int ID = scriptIndex->entityID;

				*scriptIndex = *(scriptIndex->nextScript);
				scriptIndex->entityID = ID;

				//address passing for "goto" type events.
				switch (scriptIndex->event.eventType)
				{
				case CRE_EVENT_IF_GOTO:
					scriptIndex->event.generic4.pointer = &*scriptIndex;
					scriptIndex->frameCount = 1;

					break;
				case CRE_EVENT_GOTO:
					scriptIndex->event.generic2.pointer = &*scriptIndex;
					scriptIndex->frameCount = 1;

				default:
					break;
				}

				pushEvent(scriptIndex);
			}
		}

		if (!scriptDeleted)
			(scriptIndex->frameCount)--;

		if (scriptList.empty())
			break;
	}
}