#include "eventHandler.h"

extern vector<CRE_Entity*> entityBlock;

extern queue<CRE_Script>    primitiveScriptQueue;
extern queue<CRE_Event> primitiveEventQueue;

extern CRE_Video CREVideo;
extern CRE_Audio CREAudio;


void CRE_EventHandler::queueEvent(CRE_Event e, unsigned int ID)
{
	e.entityID = ID;
	CREEventQueue.push(e);
}

void CRE_EventHandler::passQuitEvent()
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

bool CRE_EventHandler::processEvents()
{
	queuePrimitiveEvents();

	CRE_Event e;

	while (!CREEventQueue.empty())
	{
		e = CREEventQueue.front();
		CREEventQueue.pop();

		int tempID;

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
			entityFromID(e.entityID)->setTexture( * (CRE_TextureData*) (e.generic1.pointer) );
			break;
#endif

#ifdef EVENT_LOAD_ANIMATION
		case CRE_EVENT_LOAD_ANIMATION:
			entityFromID(e.entityID)->setAnimation( (CRE_AnimationPtr) (e.generic1.pointer), (CRE_AnimationFlag) e.generic2.data );
			break;
#endif

#ifdef EVENT_LOAD_GROUNDS
		case CRE_EVENT_LOAD_GROUNDS:
			loadGround(* ( CRE_GroundData*) e.generic1.pointer);
			break;
#endif

#ifdef EVENT_SET_GROUNDS
		case CRE_EVENT_SET_GROUNDS:
			setGround(* (CRE_GroundData*) e.generic1.pointer);
			break;
#endif

#ifdef EVENT_RESET_GROUNDS
		case CRE_EVENT_RESET_GROUNDS:
			resetGround();
			break;
#endif
			
#ifdef EVENT_LOAD_SCRIPT
		case CRE_EVENT_LOAD_SCRIPT:
			primitiveScriptQueue.push( * (CRE_Script*) e.generic1.pointer);
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
				//replace the value at the address of the old script (generic4) with conditional goto script (generic3)
				try
				{
					if (e.generic4.pointer == NULL)
						throw 0;

						tempID = ((const CRE_Script*)e.generic4.pointer)->entityID;
					*(CRE_Script*)e.generic4.pointer = *(CRE_Script*)e.generic3.function(NULL, NULL);
					((CRE_Script*)e.generic4.pointer)->entityID = tempID;

				}
				catch(int)
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

				tempID = ((const CRE_Script*)e.generic2.pointer)->entityID;
				*(CRE_Script*)e.generic2.pointer = *(CRE_Script*)e.generic1.function(NULL, NULL);
				((CRE_Script*)e.generic2.pointer)->entityID = tempID;

			}
			catch (int)
			{
				printf("Error in CRE_EVENT_GOTO: generic2 was NULL");
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

void CRE_EventHandler::queuePrimitiveEvents()
{
	while (!primitiveEventQueue.empty())
	{
		queueEvent(primitiveEventQueue.front());
		primitiveEventQueue.pop();
	}
}

void CRE_EventHandler::queueEvent(CRE_Event e)
{
	CREEventQueue.push(e);
}