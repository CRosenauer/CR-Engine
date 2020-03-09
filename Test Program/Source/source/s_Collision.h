#ifndef S_COLLISION_H
#define S_COLLISION_H

namespace s_Collision
{


	//enum used for referencing specific colission directions
	enum S_COLLISION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	/*
	 * checkCollision
	 *
	 * This function checks collision for the 4 cardian directions based on the
	 * entity's position and collision box, along with the game's current collision
	 * data.
	 *
	 * @Param ID: the entity who's ID you want to check
	 *
	 * @Param collision data: Place holder name. Some struct representing maps current collision.
	 *
	 * @Param collision: boolean array for the collision of the entity.
	 *
	 */
	void checkCollision(const unsigned int& ID, /*collision data,*/ bool collision[4]);
}

#endif //S_COLLISION_H