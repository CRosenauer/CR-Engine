#ifndef TESTSCRIPT_HPP
#define TESTSCRIPT_HPP

#include "script.h"

const CRE_Event testEvent02 =
{

	CRE_EVENTTYPE_ENTITY_MOVE,
	128,
	128
};

const CRE_Event testEvent01 =
{
	CRE_EVENTTYPE_TEST_PRINT,
	2,
	NULL
};

const CRE_Event testEvent00 =
{

	CRE_EVENTTYPE_TEST_PRINT,
	1,
	NULL
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