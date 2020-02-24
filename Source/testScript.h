#ifndef TESTSCRIPT_H
#define TESTSCRIPT_H

#include <SDL.h>

#include "entity.h"
#include "event.h"
#include "script.h"
#include "testTexture.hpp"
#include "testGrounds.hpp"
#include "testAnim.hpp"
#include "video.h"

//unnamed namespace to prevent other sources from directly calling these funcitons
namespace TSF
{
	void TE__testPrint(void* unused, char* text);

	void TE__moveEntity(entity* entity, SDL_Point* pos);

	void TE__validatePos(entity* entity, SDL_Point* pos);

	void TE__validateDestRect(entity* entity, SDL_Point* pos);

	void TE__moveViewport(void* unused, SDL_Point* pos);

	void TE__validateViewport(void* unused, SDL_Point* pos);

	bool returnTrue(void* unused1, void* unused2);

	const script* returnTestScript04(void* unused1, void* unused2);

	void ST_testPrintf_1(void* unused1, void* unused2);
	void ST_testPrintf_2(void* unused1, void* unused2);
	void ST_testPrintf_3(void* unused1, void* unused2);
	void ST_testPrintf_4(void* unused1, void* unused2);
	void ST_testPrintf_5(void* unused1, void* unused2);

	const script* returnScriptTest12(void* unused1, void* unused2);
}

const SDL_Point testPos = { 128, 128 };

/*
const CRE_Event testEvent =
{
	CRE_EVENT_SET_FUNCTION,
	{NULL},
	{NULL},
	{NULL},
	{NULL},
	0
};
*/

const SDL_Point testPoint = { 128, 128 };
const SDL_Point viewportTestPoint = { 32, 32 };

//checs viewport's position as (32, 32)
const CRE_Event viewportTest04 =
{
	CRE_EVENT_FUNCTION,
	{TSF::TE__validateViewport},
	(void*) &viewportTestPoint,
	NULL,
	NULL,
	0
};


/* scripting test set */

const CRE_Event scriptTestEvent20 =
{
	CRE_EVENT_FUNCTION,

	{TSF::ST_testPrintf_4},
	{NULL},
	{NULL},
	{NULL},

	NULL
};

const CRE_Event scriptTestEvent12 =
{
	CRE_EVENT_FUNCTION,

	{TSF::ST_testPrintf_5},
	{NULL},
	{NULL},
	{NULL},

	NULL
};

const CRE_Event scriptTestEvent11 =
{
	CRE_EVENT_GOTO,
	{TSF::returnScriptTest12},
	{NULL},
	{NULL},
	{NULL},

	NULL
};

const CRE_Event scriptTestEvent10 =
{
	CRE_EVENT_FUNCTION,

	{TSF::ST_testPrintf_3},
	{NULL},
	{NULL},
	{NULL},

	NULL
};

const CRE_Event scriptTestEvent01 =
{
	CRE_EVENT_FUNCTION,

	{TSF::ST_testPrintf_2},
	{NULL},
	{NULL},
	{NULL},

	NULL
};

const CRE_Event scriptTestEvent00 =
{
	CRE_EVENT_FUNCTION,

	{TSF::ST_testPrintf_1},
	{NULL},
	{NULL},
	{NULL},

	NULL
};


const script scriptTest20 =
{
	scriptTestEvent20,
	2,
	0,
	NULL
};

const script scriptTest12 =
{
	scriptTestEvent12,
	0,
	0,
	NULL
};

const script scriptTest11 =
{
	scriptTestEvent11,
	0,
	0,
	NULL
};

const script scriptTest10 =
{
	scriptTestEvent10,
	1,
	0,
	&scriptTest11
};

const script scriptTest01 =
{
	scriptTestEvent01,
	0,
	0,
	NULL
};

const script scriptTest00 =
{
	scriptTestEvent00,
	0,
	0,
	&scriptTest01
};





//moves viewport tp (32, 32)
const CRE_Event viewportTest03 =
{
	CRE_EVENT_FUNCTION,
	{TSF::TE__moveViewport},
	(void*) &viewportTestPoint,
	NULL,
	NULL,
	0
};

//checks entity's texture top-left corner is (120, 120)
const CRE_Event viewportTest02 =
{
	CRE_EVENT_FUNCTION,
	{TSF::TE__validateDestRect},
	(void*) &testPoint,
	NULL,
	NULL,
	0
};

//checks entity's position is (128, 128)
const CRE_Event viewportTest01 =
{
	CRE_EVENT_FUNCTION,
	{TSF::TE__validatePos},
	(void*) &testPoint,
	NULL,
	NULL,
	0
};

//moves entity to (128, 128)
const CRE_Event viewportTest00 =
{
	CRE_EVENT_FUNCTION,
	{TSF::TE__moveEntity},
	(void*) &testPoint,
	NULL,
	NULL,
	0
};

const script viewportTestScript04 =
{
	viewportTest04,
	0,
	0,

	NULL
};

const script viewportTestScript03 =
{
	viewportTest03,
	0,
	0,

	(script*)&viewportTestScript04
};

const script viewportTestScript02 =
{
	viewportTest02,
	0,
	0,

	(script*)&viewportTestScript03
};

const script viewportTestScript01 =
{
	viewportTest01,
	0,
	0,

	(script*)&viewportTestScript02
};

const script viewportTestScript00 = 
{
	viewportTest00,
	0,
	0,

	(script*)&viewportTestScript01
};

const CRE_Event testEvent08 =
{
	CRE_EVENT_IF_GOTO,
	(void*) TSF::returnTrue,
	{NULL},
	(void*) TSF::returnTestScript04,
	{NULL},
	0
};

const CRE_Event testEvent07 =
{
	CRE_EVENT_LOAD_ANIMATION,
	( void* ) &testAnimation00,
	( void* ) ANIMATION_LOOP,
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent06 =
{
	CRE_EVENT_RESET_GROUNDS,
	{NULL},
	{NULL},
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent05 =
{
	CRE_EVENT_SET_GROUNDS,
	(void*) &test_ground,
	{NULL},
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent04 =
{
	CRE_EVENT_LOAD_TEXTURE,
	( void* ) &ship,
	{NULL},
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent03 =
{
	CRE_EVENT_FUNCTION,
	{ TSF::TE__validatePos },
	(void*) &testPos,
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent02 =
{
	CRE_EVENT_FUNCTION,
	{ TSF::TE__moveEntity },
	( void* ) &testPos,
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent01 =
{
	CRE_EVENT_LOAD_MUSIC,
	( void* ) "Friday_Chinatown.mp3",
	{NULL},
	{NULL},
	{NULL},
	0
};

const CRE_Event testEvent00 =
{
	CRE_EVENT_LOAD_SFX,
	( void* ) "Shine.wav",
	{NULL},
	{NULL},
	{NULL},
	0
};

const struct script testScript08 =
{
	testEvent08,
	0,
	1,
	NULL
};

const struct script testScript07 =
{
	testEvent07,
	120,
	1,
	&testScript08
};

const struct script testScript06 =
{
	testEvent06,
	0,
	1,
	&testScript07
};

const struct script testScript05 =
{
	testEvent05,
	0,
	1,
	NULL
};

const struct script testScript04 =
{
	testEvent04,
	0,
	1,
	&testScript05
};

const struct script testScript03 =
{
	testEvent03,
	0,
	1,
	&testScript04
};

const struct script testScript02 =
{
	testEvent02,
	0,
	1,

	&testScript03
};

const struct script testScript01 =
{
	testEvent01,
	0,
	1,

	&testScript04
};

const struct script testScript00 =
{
	testEvent00,
	0,
	1,

	&testScript01
};

#endif //TESTSCRIPT_H