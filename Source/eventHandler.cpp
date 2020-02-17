#include "eventHandler.h"

extern vector<entity*> entityBlock;

extern queue<script>    primitiveScriptQueue;
extern queue<CRE_Event> primitiveEventQueue;

extern video CREVideo;
extern audio CREAudio;


void eventHandler::queueEvent(CRE_Event e, unsigned int ID)
{
	e.entityID = ID;
	CREEventQueue.push(e);
}

void eventHandler::passQuitEvent()
{
	CRE_Event e = 
	{
		//event code
		CRE_EVENT_QUIT,
		
		//generic data unions
		{NULL},
		{NULL},
		{NULL},
		{NULL},
		
		//reference IDs
		NULL
	};
	
	CREEventQueue.push(e);
}

bool eventHandler::processEvents()
{
	queuePrimitiveEvents();

	CRE_Event e;

	while (!CREEventQueue.empty())
	{
		e = CREEventQueue.front();
		CREEventQueue.pop();

		switch (e.eventType)
		{
#ifdef EVENT_QUIT
		case CRE_EVENT_QUIT:
			passQuitEvent();
			return false;
			break;
#endif

#ifdef EVENT_LOAD_SFX
		case CRE_EVENT_LOAD_SFX:
			CREAudio.loadSFX( (char*) (e.generic1.pointer) );
			break;
#endif

#ifdef EVENT_LOAD_MUSIC
		case CRE_EVENT_LOAD_MUSIC:
			CREAudio.loadMusic( (char*) (e.generic1.pointer) );
			break;
#endif

#ifdef EVENT_LOAD_TEXTURE
		case CRE_EVENT_LOAD_TEXTURE:
			entityFromID(e.entityID)->setTexture( * (texture*) (e.generic1.pointer) );
			break;
#endif

#ifdef EVENT_LOAD_ANIMATION
		case CRE_EVENT_LOAD_ANIMATION:
			entityFromID(e.entityID)->setAnimation( (animationPtr) (e.generic1.pointer), (ANIMATION_FLAG) e.generic2.data );
			break;
#endif

#ifdef EVENT_LOAD_GROUNDS
		case CRE_EVENT_LOAD_GROUNDS:
			loadGround(* ( groundData*) e.generic1.pointer);
			break;
#endif

#ifdef EVENT_SET_GROUNDS
		case CRE_EVENT_SET_GROUNDS:
			setGround(* (groundData*) e.generic1.pointer);
			break;
#endif

#ifdef EVENT_RESET_GROUNDS
		case CRE_EVENT_RESET_GROUNDS:
			resetGround();
			break;
#endif
			
#ifdef EVENT_LOAD_SCRIPT
		case CRE_EVENT_LOAD_SCRIPT:
			primitiveScriptQueue.push( * (script*) e.generic1.pointer);
			break;
#endif

#ifdef EVENT_FUNCTION
		case CRE_EVENT_FUNCTION:
			(void) e.generic1.function( entityFromID(e.entityID), e.generic2.pointer );
			break;
#endif

#ifdef EVENT_IF_GOTO
		case CRE_EVENT_IF_GOTO:
			if ( (bool) e.generic1.function( entityFromID(e.entityID), e.generic2.pointer ) )
			{
				//replace the value at the address of the old script with conditional goto script
				* (script*) e.generic3.pointer = * (script*) e.generic2.pointer;
			}
				
			break;
#endif

		default:
			printf("Unknown event code: %i. Skipping event.\nPlease refer to event.h, enum CREEventCode\n", e.eventType);
			break;
		}
	}
	
	return true;
}

void eventHandler::queuePrimitiveEvents()
{
	while (!primitiveEventQueue.empty())
	{
		queueEvent(primitiveEventQueue.front());
		primitiveEventQueue.pop();
	}
}

void eventHandler::queueEvent(CRE_Event e)
{
	CREEventQueue.push(e);
}