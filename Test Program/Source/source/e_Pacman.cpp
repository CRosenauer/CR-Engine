#include "e_Pacman.h"

#include "../entityHandler.h"

namespace e_Pacman
{
	namespace logic
	{
		void moveUp(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);
			if (pacman != NULL)
				pacman->setVelocity(0, -moveVecocity, 0);
		}

		void moveDown(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);
			if (pacman != NULL)
				pacman->setVelocity(0, moveVecocity, 0);
		}

		void moveRight(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);
			if (pacman != NULL)
				pacman->setVelocity(moveVecocity, 0, 0);
		}

		void moveLeft(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);
			if (pacman != NULL)
				pacman->setVelocity(-moveVecocity, 0, 0);
		}

		void stop(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);
			if(!pacman)
				pacman->setVelocity(0, 0, 0);
		}

		enums::direction getDirection(const int& ID)
		{
			int velocity[3];

			CRE_Entity* pacman = entityFromID(ID);
			
			pacman->getVelocity(velocity);

			if (velocity[0] != 0)
			{
				if (velocity[0] > 0)
					enums::direction::RIGHT;
				else
					enums::direction::LEFT;
			}
			if (velocity[1] != 0)
			{
				if (velocity[1] > 0)
					enums::direction::DOWN;
				else
					enums::direction::UP;
			}

			return enums::direction::NONE;
		}

		SDL_Rect getCollisionRect(const int& ID)
		{
			CRE_Entity* pacman = entityFromID(ID);

			CRE_EntityData data;
			pacman->getEntityData(data);

			return data.componentData.pacman.collision;
			//ey dog i heard you like member variables. so we gave your member variable a member variable
		}
	}
}