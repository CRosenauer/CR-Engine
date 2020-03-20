#ifndef E_PACMAN_H
#define E_PACMAN_H

#include "../texture.h"

#include "SDL_rect.h"

namespace e_Pacman
{
	const unsigned short moveVecocity = 1;

	namespace entityData
	{
		struct pacmanData
		{
			//x, y offsets for corner of collision box relative to entity position.
			//w, h size of collision box.
			SDL_Rect collision;
		};

		const struct pacmanData pacmanData =
		{
			{-4, -4, 8, 8}
		};
	}

	namespace imageDat
	{
		const CRE_TextureData pacmanSprite =
		{
			"pacman.png",  //image name
			{0, 0, 12, 13},//where to draw from
			6,  //image offsets to position texture relative to entity point
			6,

			255 //alpha
		};

		//const CRE_Animation deathAnimation =
		//{
			
		//};
	}

	namespace logic
	{
		//movement functions
		//sets entity's velocity 
		void moveUp(const int& ID);
		void moveDown(const int& ID);
		void moveRight(const int& ID);
		void moveLeft(const int& ID);
		void stop(const int& ID);
	}
}

#endif //E_PACMAN_H
