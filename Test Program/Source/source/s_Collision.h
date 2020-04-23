#ifndef S_COLLISION_H
#define S_COLLISION_H

#include "SDL_rect.h"

#include "s_Tiling.h"

#include "e_Pacman.h"

namespace s_Collision
{
	const SDL_Rect mapCollisionRect = { 0, 0, 8, 8 };

	/*
	 * moveEntity
	 *
	 * This moves the entity of the passed ID and checks for collision with the game map.
	 * If the entity is to collide with the game map, entity is moved to the position right
	 * before collision.
	 *
	 * @Param ID: the ID of the entity that you want to move.
	 *
	 * @Param dir: Direction which the entity will move in.
	 *
	 */
	void moveEntity(const unsigned int& ID, e_Pacman::enums::direction dir);

	/*
	 * checkCollision
	 *
	 * This function checks collision for the 4 cardian directions based on the
	 * entity's position and collision box, along with the game's current collision
	 * data.
	 *
	 * @Param ID: the entity who's ID you want to check
	 *
	 * @Param map: Struct representing map's tile set. Tile set used for collision.
	 *
	 */
	bool checkCollision(const unsigned int& ID, const s_Tiling::tileMap& map);

	/*
	 * updateCollisionPosition
	 *
	 * This function moves the entity to the position right before colliding with the game map.
	 * Function is not fully tested if no collision is to occur so don't use this unless you know
	 * a collision is occuring.
	 *
	 * @Param ID: the entity who's ID you want to check
	 *
	 * @Param map: Struct representing map's tile set. Tile set used for collision.
	 *
	 */
	void updateCollisionPosition(const unsigned int& ID, const s_Tiling::tileMap& map);
}

#endif //S_COLLISION_H