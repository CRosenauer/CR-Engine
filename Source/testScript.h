#ifndef TESTSCRIPT_H
#define TESTSCRIPT_H

#include <SDL.h>

#include "entity.h"
#include "event.h"
#include "script.h"
#include "testTexture.hpp"
#include "testGrounds.hpp"
#include "testAnim.hpp"

//unnamed namespace to prevent other sources from directly calling these funcitons
namespace TSF
{
	void TE__testPrint(void* unused, char* text);

	void TE__moveEntity(entity* entity, SDL_Point* pos);

	void TE__validatePos(entity* entity, SDL_Point* pos);

	bool returnTrue(void* unused1, void* unused2);

	const script* returnTestScript04(void* unused1, void* unused2);
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
	120,
	1,
	&testScript06
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

	&testScript02
};

const struct script testScript00 =
{
	testEvent00,
	0,
	1,

	&testScript01
};

#endif //TESTSCRIPT_H