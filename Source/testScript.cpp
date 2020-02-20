#include "testScript.h"

namespace TSF
{
	void TE__testPrint(void* unused, char* text)
	{
		printf("%s\n", text);
	}

	void TE__moveEntity(entity* entity, SDL_Point* pos)
	{
		int tempPos[3];

		entity->getPosition(tempPos);
		tempPos[0] = pos->x;
		tempPos[1] = pos->y;

		entity->setPosition(tempPos[0], tempPos[1], tempPos[2]);
	}

	void TE__validatePos(entity* entity, SDL_Point* pos)
	{
		int tempPos[3];

		entity->getPosition(tempPos);

		if (tempPos[0] == pos->x && tempPos[1] == pos->y)
			printf("Test passed: CRE_EVENT_FUNCTION\n");
		else
			printf("Test failed: CRE_EVENT_FUNCTION\n");
	}

	bool returnTrue(void* unused1, void* unused2)
	{
		return true;
	}

	const script* returnTestScript04(void* unused1, void* unused2)
	{
		return &testScript04;
	}
}