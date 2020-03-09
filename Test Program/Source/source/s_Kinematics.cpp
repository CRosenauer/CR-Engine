#include "s_Kinematics.h"

#include "../entityHandler.h"

namespace s_Kinematics
{
	void updateKinematics(const unsigned int& ID)
	{
		int tempVector1[3] = { 0, 0, 0 };
		int tempVector2[3] = { 0, 0, 0 };
		CRE_Entity* entity = entityFromID(ID);

		entity->getVelocity(tempVector1);
		entity->getAcceleration(tempVector2);
		
		//perform v = v0 + a*dt
		for (int i = 0; i < 3; i++)
			tempVector1[i] += tempVector2[i];

		entity->getPosition(tempVector2);

		//perform s = s0 + v*dt
		for (int i = 0; i < 3; i++)
			tempVector2[i] += tempVector1[i];

		entity->setPosition(tempVector2[0], tempVector2[1], tempVector2[2]);
		entity->setVelocity(tempVector1[0], tempVector1[1], tempVector1[2]);
	}
}
