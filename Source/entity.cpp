#include "entity.h"

static unsigned int IDCounter = 0;

entity::entity()
{
	posX = 0;
	posY = 0;
	posZ = 0;
	velX = 0;
	velY = 0;
	velZ = 0;
	accX = 0;
	accY = 0;
	accZ = 0;
	animFrameCount = 0;
	eAnimation = NULL;
	eFirstAnimation = NULL;
	renderingFlag = RENDERINGFLAG_SPRITE;
	entityID = ++IDCounter;
}

void entity::setTexture(const textureData& text)
{
	SDL_Rect dest = text.source;

	dest.x = posX;
	dest.y = posY;

	eTexture.loadTexture(text, dest);
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
	return &eTexture;
}

void entity::setPosition(int x, int y, int z)
{
	SDL_Rect tempDest = eTexture.getDestRect();

	tempDest.x += (x - posX);
	posX = x;

	tempDest.y += (y - posY);
	posY = y;

	if (z > 0)
		posZ = z;
	else
		posZ = 0;

	eTexture.setRect(eTexture.getSourceRect(), tempDest);
}

void entity::setVelocity(int x, int y, int z)
{
	velX = x;
	velY = y;
	velZ = z;
}

void entity::setAcceleration(int x, int y, int z)
{
	accX = x;
	accY = y;
	accZ = z;
}

void entity::getPosition(int pos[3])
{
	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;
}

void entity::getVelocity(int vel[3])
{
	vel[0] = velX;
	vel[1] = velY;
	vel[2] = velZ;
}

void entity::getAcceleration(int acc[3])
{
	acc[0] = accX;
	acc[1] = accY;
	acc[2] = accZ;
}

void entity::setAnimation(const animation* anim, const ANIMATION_FLAG& flag)
{
	eAnimation = anim;

	animFrameCount = eAnimation->frameCount;

	if (flag == ANIMATION_LOOP)
		eFirstAnimation = anim;

	setTexture(eAnimation->textureData);
}

unsigned int entity::getEntityID()
{
	return entityID;
}

int entity::getDepth()
{
	return posZ;
}

RENDERINGFLAG entity::getRenderingFlag()
{
	return renderingFlag;
}

void entity::setRenderingFlag(RENDERINGFLAG flag)
{
	renderingFlag = flag;
}

void entity::setEntityType(const unsigned int& i)
{
	data.entityType = i;
}

unsigned int entity::getEntityType()
{
	return data.entityType;
}

SDL_Rect entity::getTextureDest()
{
	return eTexture.getDestRect();
}

void entity::updateAnimation()
{
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

		setTexture(eAnimation->textureData);
	}
}