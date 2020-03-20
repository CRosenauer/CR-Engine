#include "s_Collision.h"

namespace s_Collision
{
	//stub.
	void checkCollision(const unsigned int& ID, const s_Tiling::tileMap& map, bool collision[4])
	{
		collision[UP] = false;
		collision[DOWN] = false;
		collision[RIGHT] = false;
		collision[LEFT] = false;
	}

	//stub
	bool validateMove()
	{
		return true;
	}
}