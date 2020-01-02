#ifndef TESTSCRIPT_HPP
#define TESTSCRIPT_HPP

#include "script.h"

const SDL_Event testEvent02 =
{

};

const SDL_Event testEvent01 =
{

};

const SDL_Event testEvent00 =
{

};

const struct script testScript02 =
{
	testEvent02,
	30,
	1,
	NULL
};

const struct script testScript01 =
{
	testEvent01,
	30,
	1,
	&testScript02
};

const struct script testScript00 =
{
	testEvent00,
	30,
	1,
	&testScript01
};

#endif //TESTSCRIPT_HPP