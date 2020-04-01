#include "s_Tiling.h"

#include "../entityHandler.h"
#include "../texture.h"

extern vector<CRE_Entity*> entityBlock;

namespace
{
	static bool mapLoaded  = false;
	static bool mapVisible = false;
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
						entity = allocateEntityPtr(TILE);
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						
						break;

					case BORDER_WALL:
						entity = allocateEntityPtr(TILE);
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;

					case DEN_WALL:
						entity = allocateEntityPtr(TILE);
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;

					case DEN_GATE:
						entity = allocateEntityPtr(TILE);
						entity->setTexture(imageData::wall);
						entity->setPosition(j * TILEWIDTH, 8 * HEADERHEIGHT + i * TILEWIDTH, 0);
						entity->setRenderingFlag(RENDERINGFLAG_BACKGROUND);
						break;
					}
				}
			}

			mapLoaded = true;
		}

		if (!mapVisible)
		{
			int size = entityBlock.size();
			for (int i = 0; i < size; i++)
			{
				if (entityBlock[i]->getEntityType() == TILE)
				{
					entityBlock[i]->setAlpha(255);
				}
			}

			mapVisible = true;
		}
	}

	void unloadMap()
	{
		if (mapVisible)
		{
			int size = entityBlock.size();
			for (int i = 0; i < size; i++)
			{
				if (entityBlock[i]->getEntityType() == TILE)
				{
					entityBlock[i]->setAlpha(0);
				}
			}

			mapVisible = false;
		}
	}
}