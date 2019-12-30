#include "entity.h"

#include <cassert>

static unsigned int IDCounter = 0;

entity::entity()
{
	posX = 0;
	posY = 0;
	posZ = 0;
	defined = false;
	animFrameCount = 0;
	eAnimation = NULL;
	eFirstAnimation = NULL;
	renderingFlag = RENDERINGFLAG_SPRITE;
	entityID = NULL;
}

void entity::setTexture(const std::string& path, SDL_Rect source, const int& xOffset, const int& yOffset)
{
	SDL_Rect dest = source;
	
	SDL_Rect tempSource;

	dest.x = posX;
	dest.y = posY;

	if (rectIsUndefined(source))
	{
		tempSource = eTexture.getSourceRect();
	}
	else
	{
		tempSource = source;
	}

	eTexture.loadTexture(path, tempSource, dest, xOffset, yOffset);
}

bool entity::rectIsUndefined(SDL_Rect rect)
{
	return (rect.x < 0)||(rect.y < 0)||(rect.w < 0)||(rect.h < 0);
}

void entity::setTexture(const texture& text)
{
	eTexture = text;
}

texture* entity::getTexture()
{
	//Updates animation if entity is currently using an animation.
	if (eAnimation != NULL)
	{

		//checks for animation frame count, cycles to the next frame of animation.
		if (animFrameCount == 0)
		{
			//checks if there is a next frame in the animation.
			if (eAnimation->nextFrame == NULL)
			{
				//checks for looping animation. if looping animation then
				//cycles to the next (first) frame of animation
				if (eFirstAnimation != NULL)
				{
					eAnimation = eFirstAnimation;
					animFrameCount = eAnimation->frameCount;
				}
			}
			else
			{
				eAnimation = eAnimation->nextFrame;
				animFrameCount = eAnimation->frameCount;
			}
		}

		animFrameCount--;

		setTexture(eAnimation->path, eAnimation->source, eAnimation->xOffset, eAnimation->yOffset);
	}

	printf("Pass getTexture\nEntity ID: %i\n", entityID);

	SDL_Rect source = eTexture.getDestRect();

	printf("EntityID: %i, source.x: %i\n", entityID, source.x);
	printf("EntityID: %i, source.y: %i\n", entityID, source.y);
	printf("EntityID: %i, source.w: %i\n", entityID, source.w);
	printf("EntityID: %i, source.h: %i\n", entityID, source.h);

	return &eTexture;
}

void entity::setPosition(int x, int y, int z)
{
	SDL_Rect temp = eTexture.getDestRect();


	temp.x += (x - posX);
	posX = x;

	temp.y += (y - posY);
	posY = y;

	posZ = z;

	eTexture.setRect(eTexture.getSourceRect(), temp);
}

void entity::getPosition(int pos[3])
{
	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;
}

void entity::setAnimation(const animation* anim, const CREAnimationFlag& flag)
{
	eAnimation = anim;

	animFrameCount = eAnimation->frameCount;

	if (flag == ANIMATION_LOOP)
		eFirstAnimation = anim;

	setTexture(eAnimation->path, eAnimation->source, eAnimation->xOffset, eAnimation->yOffset);
}

bool entity::isDefined()
{
	return defined;
}

void entity::define()
{
	defined = true;
	entityID = ++IDCounter;
}

unsigned int entity::getEntityID()
{
	return entityID;
}

int entity::getDepth()
{
	return posZ;
}

CREVRenderingFlag entity::getRenderingFlag()
{
	return renderingFlag;
}

void entity::setRenderingFlag(CREVRenderingFlag flag)
{
	renderingFlag = flag;
}