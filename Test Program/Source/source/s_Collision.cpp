#include "s_Collision.h"

#include "../entityHandler.h"
#include "s_Tiling.h"
#include "s_Kinematics.h"

namespace s_Collision
{
	void moveEntity(const unsigned int& ID, e_Pacman::enums::direction dir)
	{
		CRE_Entity* entity = entityFromID(ID);

		e_Pacman::enums::direction prevDirection = e_Pacman::enums::direction::NONE;

		int prevVelocity[3];
		int velocity[3] = { 0, 0, 0 };
		entity->getVelocity(prevVelocity);

		//check entity Direction
		if (prevVelocity[0] > 0)
			prevDirection = e_Pacman::enums::direction::RIGHT;
		else if (prevVelocity[0] < 0)
			prevDirection = e_Pacman::enums::direction::LEFT;
		else if (prevVelocity[1] > 0)
			prevDirection = e_Pacman::enums::direction::DOWN;
		else if (prevVelocity[1] < 0)
			prevDirection = e_Pacman::enums::direction::UP;

		switch (dir)
		{
		default:
		case e_Pacman::enums::direction::NONE:
			break;

		case e_Pacman::enums::direction::UP:
			velocity[1] = -e_Pacman::moveVecocity;
			break;

		case e_Pacman::enums::direction::DOWN:
			velocity[1] = e_Pacman::moveVecocity;
			break;

		case e_Pacman::enums::direction::RIGHT:
			velocity[0] = e_Pacman::moveVecocity;
			break;

		case e_Pacman::enums::direction::LEFT:
			velocity[0] = -e_Pacman::moveVecocity;
			break;
		}

		entity->setVelocity(velocity[0], velocity[1], prevVelocity[2]);

		//check collision
		if (checkCollision(ID, s_Tiling::gameMap))
		{
			if (dir != prevDirection)
			{
				entity->setVelocity(prevVelocity[0], prevVelocity[1], prevVelocity[2]);

				if (checkCollision(ID, s_Tiling::gameMap))
				{
					updateCollisionPosition(ID, s_Tiling::gameMap);
					entity->setVelocity(0, 0, velocity[2]);
				}
			}
			else
			{
				updateCollisionPosition(ID, s_Tiling::gameMap);
				entity->setVelocity(0, 0, velocity[2]);
			}
		}	

		s_Kinematics::updateKinematics(entity->getEntityID());
	}

	//stub.
	bool checkCollision(const unsigned int& ID, const s_Tiling::tileMap& map)
	{
		CRE_Entity* entity = entityFromID(ID);
		int position[3];
		int velocity[3];

		entity->getPosition(position);
		entity->getVelocity(velocity);
		position[0] += velocity[0];
		position[1] += velocity[1];

		{
			//re-usable varaibles
			SDL_Rect entityCollision;
			SDL_Rect mapCollision = mapCollisionRect;
			int i, j;
			CRE_EntityData d;
			entity->getEntityData(d);

			switch (entity->getEntityType())
			{
			case PACMAN:
				entityCollision = d.componentData.pacman.collision;
				break;

			case GHOST:
				//ghost stuff
				break;

			case DOT:
			case SUPER_DOT:
			case TEXT:
			case TILE:
			default:
				break;
			}

			entityCollision.x += position[0];
			entityCollision.y += position[1];

			for (i = 0; i < GAMEWIDTH; i++)
			{
				for (j = 0; j < GAMEHEIGHT; j++)
				{
					if (map.map[j][i] != s_Tiling::BLANK)
					{
						mapCollision.x = i * TILEWIDTH;
						mapCollision.y = (j + HEADERHEIGHT) * TILEHEIGHT;

						if (SDL_HasIntersection(&entityCollision, &mapCollision))
						{
							return true;
						}
					}
				}
			}

			return false;
		}
	}
	
	void updateCollisionPosition(const unsigned int& ID, const s_Tiling::tileMap& map)
	{

		CRE_Entity* entity = entityFromID(ID);
		int position[3];
		int velocity[3];

		entity->getPosition(position);
		entity->getVelocity(velocity);
		//position[0] += velocity[0];
		//position[1] += velocity[1];

		int xOffset = 0, yOffset = 0;

		{
			//re-usable varaibles
			SDL_Rect entityCollision;
			SDL_Rect mapCollision = mapCollisionRect;
			int i, j;
			CRE_EntityData d;
			entity->getEntityData(d);

			switch (entity->getEntityType())
			{
			case PACMAN:
				entityCollision = d.componentData.pacman.collision;
				xOffset = entityCollision.x;
				yOffset = entityCollision.y;
				break;

			case GHOST:
				//ghost stuff
				break;

			case DOT:
			case SUPER_DOT:
			case TEXT:
			case TILE:
			default:
				break;
			}

			entityCollision.x += position[0] + velocity[0];
			entityCollision.y += position[1] + velocity[1];

			bool cont = true;

			for (i = 0; i < GAMEWIDTH && cont; i++)
			{
				for (j = 0; j < GAMEHEIGHT && cont; j++)
				{
					if (map.map[j][i] != s_Tiling::BLANK)
					{
						mapCollision.x = i * TILEWIDTH;
						mapCollision.y = (j + HEADERHEIGHT) * TILEHEIGHT;

						if (SDL_HasIntersection(&entityCollision, &mapCollision))
						{
							cont = false;

							int newPosX = 0;
							int newPosY = 0;

							if (entityCollision.x + entityCollision.w > mapCollision.x&&
								entityCollision.x + entityCollision.w < mapCollision.x + mapCollision.w)
							{
								if (velocity[0] != 0)
									newPosX = mapCollision.x - entityCollision.w - xOffset;
							}
							else if (entityCollision.x < mapCollision.x + mapCollision.w &&
								entityCollision.x > mapCollision.x)
							{
								if (velocity[0] != 0)
									newPosX = mapCollision.x + mapCollision.w - xOffset;
							}

							if (entityCollision.y + entityCollision.h > mapCollision.y&&
								entityCollision.y + entityCollision.h < mapCollision.y + mapCollision.w)
							{
								if (velocity[1] != 0)
									newPosY = mapCollision.y - entityCollision.h - yOffset;
							}
							else if (entityCollision.y < mapCollision.y + mapCollision.h &&
								entityCollision.y > mapCollision.y)
							{
								if (velocity[1] != 0)
									newPosY = mapCollision.y + mapCollision.h - yOffset;
							}
						}
					}
				}
			}
		}
	}
}