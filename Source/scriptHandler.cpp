#include "scriptHandler.h"

extern queue<script>    primitiveScriptQueue;
extern queue<CRE_Event> primitiveEventQueue;

namespace
{
	//boolean function to remove complete scripts
	//to be used by list::remove_if
	bool scriptComplete(const script& script) { return script.frameCount < 0 && script.nextScript == NULL; };
}

void scriptHandler::loadScript(script eScript, unsigned int ID)
{
	//script is pushed to the front of the list
	//order of this list doesn't really matter
	scriptList.push_front(eScript);
	scriptIndex = scriptList.begin();

	//sets reference ID of passed event
	if (ID != NULL)
		scriptIndex->entityID = ID;
}

void scriptHandler::pushEvent(const std::list<script>::iterator& scriptLoc)
{
	scriptLoc->event.entityID = scriptLoc->entityID;
	primitiveEventQueue.push(scriptLoc->event);
}

//broken function. rewrite.
void scriptHandler::processScripts()
{
	//traverses script list and processes each event in the script list.
	for (scriptIndex = scriptList.begin(); scriptIndex != scriptList.end(); scriptIndex++)
	{
		//if frameCount of a given script == 0 (script last for 0 frames (instant) or script has passed its delay)
		while (scriptIndex->frameCount == 0)
		{
			/* process and load current script */

			//address passing for "goto" type events.
			switch (scriptIndex->event.eventType)
			{
#ifdef EVENT_IF_GOTO
			case CRE_EVENT_IF_GOTO:
				scriptIndex->event.generic4.pointer = &*scriptIndex;
				processGotoEvent(*scriptIndex);

				break;
#endif

#ifdef EVENT_GOTO
			case CRE_EVENT_GOTO:
				scriptIndex->event.generic2.pointer = &*scriptIndex;
				processGotoEvent(*scriptIndex);
#endif

			default:
				break;
			}

			//load event from current script frame
			pushEvent(scriptIndex);


			/* iterate to next script in curent script list index */

			//goto next event in script (if there is one)
			if (scriptIndex->nextScript != NULL)
			{
				//sets script to next script and pushes the next script to event queue.
				int ID = scriptIndex->entityID;

				*scriptIndex = *(scriptIndex->nextScript);
				scriptIndex->entityID = ID;
			}
			else
			{
				break;
			}
		}

		//decrement frame count
		(scriptIndex->frameCount)--;
	}


	/* remove completed scripts */
	scriptList.remove_if(scriptComplete);
}

void scriptHandler::processGotoEvent(script s)
{
	//set up temp holding variables
	int tempID = s.entityID;
	CRE_Event e = s.event;

	switch(e.eventType)
	{ 
#ifdef EVENT_IF_GOTO
		case CRE_EVENT_IF_GOTO:
			if ((bool)e.generic1.function(entityFromID(e.entityID), e.generic2.pointer))
			{
				//replace the value at the address of the old script (generic4) with conditional goto script (generic3)
				try
				{
					if (e.generic4.pointer == NULL)
						throw 0;

					tempID = ((const script*)e.generic4.pointer)->entityID;
					*(script*)e.generic4.pointer = *(script*)e.generic3.function(NULL, NULL);
					((script*)e.generic4.pointer)->entityID = tempID;

				}
				catch (int)
				{
					printf("Error in CRE_EVENT_IF_GOTO: generic4 was NULL");
				}
			}

			break;
#endif

#ifdef EVENT_GOTO
		case CRE_EVENT_GOTO:
			//replace the value at the address of the old script (generic2) with the goto script (generic1)
			try
			{
				if (e.generic2.pointer == NULL)
					throw 0;

				tempID = ((const script*)e.generic2.pointer)->entityID;
				*(script*)e.generic2.pointer = *(script*)e.generic1.function(NULL, NULL);
				((script*)e.generic2.pointer)->entityID = tempID;

			}
			catch (int)
			{
				printf("Error in CRE_EVENT_GOTO: generic2 was NULL");
			}

			break;
#endif
		default:
			break;
	}
}