#include "testScript.h"

extern CRE_Video CREVideo;

namespace TSF
{
	void TE__testPrint(void* unused, char* text)
	{
		printf("%s\n", text);
	}

	void TE__moveEntity(CRE_Entity* entity, SDL_Point* pos)
	{
		int tempPos[3];

		entity->getPosition(tempPos);
		tempPos[0] = pos->x;
		tempPos[1] = pos->y;

		entity->setPosition(tempPos[0], tempPos[1], tempPos[2]);
	}

	void TE__validatePos(CRE_Entity* entity, SDL_Point* pos)
	{
		int tempPos[3];

		entity->getPosition(tempPos);

		if (tempPos[0] == pos->x && tempPos[1] == pos->y)
			printf("Test passed: entity position correct\n");
		else
			printf("Test failed: entity position incorrect\n");
	}

	void TE__validateDestRect(CRE_Entity* entity, SDL_Point* pos)
	{
		CRE_Texture tempTexture = *entity->getTexture();

		SDL_Rect validationRect = tempTexture.getDestRect();

		//hard coded values to "correct" texture position offsets
		validationRect.x += 8;
		validationRect.y += 8;

		if ((validationRect.x == pos->x) && (validationRect.y == pos->y))
			printf("Test Passed: dest rect position correct.\n");
		else
		{
			printf("Test failed: dest rect position not correct.\nActual dest rect positions: %i, %i\n", validationRect.x, validationRect.y);
		}
			
	}

	void TE__moveViewport(void* unused, SDL_Point* pos)
	{
		int posArray[] = { pos->x, pos->y };
		CREVideo.setCameraPos(posArray);
	}

	void TE__validateViewport(void* unused, SDL_Point* pos)
	{
		int posArray[2];
		CREVideo.getCameraPos(posArray);

		if ((posArray[0] == pos->x) && (posArray[1] == pos->y))
			printf("Test Passed: viewport position correct.\n");
		else
			printf("Test failed: viewport position not correct.\n");
	}

	bool returnTrue(void* unused1, void* unused2)
	{
		return true;
	}

	const CRE_Script* returnTestScript04(void* unused1, void* unused2)
	{
		return &testScript04;
	}

	const CRE_Script* returnScriptTest12(void* unused1, void* unused2)
	{
		return &scriptTest12;
	}

	void ST_testPrintf_1(void* unused1, void* unused2)
	{
		printf("You should see this on frame 0.\n");
	}

	void ST_testPrintf_2(void* unused1, void* unused2)
	{
		printf("You should also see this on frame 0.\n");
	}

	void ST_testPrintf_3(void* unused1, void* unused2)
	{
		printf("You should see this on frame 1.\n");
	}

	void ST_testPrintf_4(void* unused1, void* unused2)
	{
		printf("You should see this on frame 2.\n");
	}

	void ST_testPrintf_5(void* unused1, void* unused2)
	{
		printf("You should also see this on frame 1.\n");
	}

}

