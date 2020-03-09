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
	}
}