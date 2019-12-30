#ifndef TESTANIM_H
#define TESTANIM_H

#include "animation.h"


//a simple looping sphere that spells out "LUL"
//each frame of animation lasts for 10 CREngine frames

const animation testAnimation02 =
{
	"AnimationTest_02.png",
	{0, 0, 16, 16},
	8,
	8,
	10,
	NULL
};

const animation testAnimation01 =
{
	"AnimationTest_01.png",
	{0, 0, 16, 16},
	8,
	8,
	10,
	&testAnimation02
};

const animation testAnimation00 =
{
	"AnimationTest_00.png",
	{0, 0, 16, 16},
	8,
	8,
	10,
	&testAnimation01
};

#endif //TESTANIM_H