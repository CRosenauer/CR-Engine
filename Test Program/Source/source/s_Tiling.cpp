#include "s_Tiling.h"

#include "../entityHandler.h"
#include "../texture.h"

extern vector<CRE_Entity*> entityBlock;

namespace
{
	static bool mapLoaded = false;
}

namespace s_Tiling
{
	namespace imageData
	{
		const CRE_TextureData wall =
		{
			"testWall.png",

			{0, 0, 8, 8},

			0,
			0,

			255
		};
	}

	void loadMap()
	{
		if (!mapLoaded)
		{
			for (int i = 0; i < GAMEHEIGHT; i++)
			{
				for (int j = 0; j < GAMEWIDTH; j++)
				{
					CRE_Entity* entity;
					switch (gameMap.map[i][j])
					{
					case BLANK:
					default:
						break;

					case WALL:
						entity = entityFromID(allocateEntity(TILE));
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						
						break;

					case BORDER_WALL:
						entity = entityFromID(allocateEntity(TILE));
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;

					case DEN_WALL:
						entity = entityFromID(allocateEntity(TILE));
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;

					case DEN_GATE:
						entity = entityFromID(allocateEntity(TILE));
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;
					}
				}
			}

			mapLoaded = true;
		}
	}

	void unloadMap()
	{

		printf("%i\n", mapLoaded);
		if (mapLoaded)
		{
			for (int i = 0; i < entityBlock.size(); i++)
			{
				if (entityBlock[i]->getEntityType() == WALL ||
					entityBlock[i]->getEntityType() == BORDER_WALL ||
					entityBlock[i]->getEntityType() == DEN_WALL ||
					entityBlock[i]->getEntityType() == DEN_GATE)
					deleteEntity(entityBlock[i]->getEntityID());
			}

			mapLoaded = false;
		}
	}
}