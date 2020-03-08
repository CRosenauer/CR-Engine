#ifndef TESTANIM_H
#define TESTANIM_H

#include "animation.h"


//a simple looping sphere that spells out "LUL"
//each frame of animation lasts for 10 CREngine frames

const CRE_Animation testAnimation02 =
{
	&animationTest2,
	10,
	NULL
};

const CRE_Animation testAnimation01 =
{
	&animationTest1,
	10,
	&testAnimation02
};

const CRE_Animation testAnimation00 =
{
	&animationTest0,
	10,
	&testAnimation01
};

#endif //TESTANIM_H