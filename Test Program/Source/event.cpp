#include "event.h"

//primitive queue for holding events to load
//allows eventHandler and scriptHandler to communicate without circular dependancies
queue<CRE_Event> primitiveEventQueue;

string eventCodeToString(const CRE_EventCode& code)
{
	string s;

	switch (code)
	{
#ifdef EVENT_QUIT
	case CRE_EVENT_QUIT:
		s = "CRE_EVENT_QUIT";
		break;
#endif

#ifdef EVENT_LOAD_SFX
	case CRE_EVENT_LOAD_SFX:
		s = "CRE_EVENT_LOAD_SFX";
		break;
#endif

#ifdef EVENT_LOAD_MUSIC
	case CRE_EVENT_LOAD_MUSIC:
		s = "CRE_EVENT_LOAD_MUSIC";
		break;
#endif

#ifdef EVENT_LOAD_TEXTURE
	case CRE_EVENT_LOAD_TEXTURE:
		s = "CRE_EVENT_LOAD_TEXTURE";
		break;
#endif

#ifdef EVENT_LOAD_ANIMATION
	case CRE_EVENT_LOAD_ANIMATION:
		s = "CRE_EVENT_LOAD_ANIMATION";
		break;
#endif

#ifdef EVENT_LOAD_GROUNDS
	case CRE_EVENT_LOAD_GROUNDS:
		s = "CRE_EVENT_LOAD_GROUNDS";
		break;
#endif

#ifdef EVENT_SET_GROUNDS
	case CRE_EVENT_SET_GROUNDS:
		s = "CRE_EVENT_SET_GROUNDS";
		break;
#endif

#ifdef EVENT_RESET_GROUNDS
	case CRE_EVENT_RESET_GROUNDS:
		s = "CRE_EVENT_RESET_GROUNDS";
		break;
#endif

#ifdef EVENT_LOAD_SCRIPT
	case CRE_EVENT_LOAD_SCRIPT:
		s = "CRE_EVENT_LOAD_SCRIPT";
		break;
#endif

#ifdef EVENT_FUNCTION
	case CRE_EVENT_FUNCTION:
		s = "CRE_EVENT_FUNCTION";
		break;
#endif

#ifdef EVENT_IF_GOTO
	case CRE_EVENT_IF_GOTO:
		s = "CRE_EVENT_IF_GOTO";
		break;
#endif
	}

	return s;
}

