#ifndef TESTSCRIPT_HPP
#define TESTSCRIPT_HPP

#include "event.h"
#include "script.h"

const CRE_Event testEvent02 =
{
	CRE_EVENT_FUNCTION,
	128,
	128
};

const CRE_Event testEvent01 =
{
	CRE_EVENT_FUNCTION,
	1,
	NULL //NULL as value should not be used in print test
};

const CRE_Event testEvent00 =
{
	CRE_EVENT_FUNCTION,
	0,
	NULL //NULL as value should not be used in print test
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