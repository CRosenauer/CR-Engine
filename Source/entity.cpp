#include "entity.h"

static unsigned int IDCounter = 0;

vector<CRE_Entity*> entityBlock;

CRE_Entity::CRE_Entity()
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

void CRE_Entity::setTexture(const CRE_TextureData& text)
{
	SDL_Rect dest = text.source;

	dest.x = posX;
	dest.y = posY;

	eTexture.loadTexture(text, dest);
}

bool CRE_Entity::rectIsUndefined(SDL_Rect rect)
{
	return (rect.x < 0)||(rect.y < 0)||(rect.w < 0)||(rect.h < 0);
}

void CRE_Entity::setTexture(const CRE_Texture& text)
{
	eTexture = text;
}

CRE_Texture* CRE_Entity::getTexture()
{
	return &eTexture;
}

void CRE_Entity::setPosition(int x, int y, int z)
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

void CRE_Entity::setVelocity(int x, int y, int z)
{
	velX = x;
	velY = y;
	velZ = z;
}

void CRE_Entity::setAcceleration(int x, int y, int z)
{
	accX = x;
	accY = y;
	accZ = z;
}

void CRE_Entity::getPosition(int pos[3])
{
	pos[0] = posX;
	pos[1] = posY;
	pos[2] = posZ;
}

void CRE_Entity::getVelocity(int vel[3])
{
	vel[0] = velX;
	vel[1] = velY;
	vel[2] = velZ;
}

void CRE_Entity::getAcceleration(int acc[3])
{
	acc[0] = accX;
	acc[1] = accY;
	acc[2] = accZ;
}

void CRE_Entity::setAnimation(const CRE_Animation* anim, const CRE_AnimationFlag& flag)
{
	//set up internal animation data
	eAnimation = anim;
	animFrameCount = eAnimation->frameCount;
	if (flag == ANIMATION_LOOP)
		eFirstAnimation = anim;

	//load animation texture
	setTexture(*(eAnimation->textureData));

	//decrement frame count
	animFrameCount--;
}

unsigned int CRE_Entity::getEntityID()
{
	return entityID;
}

int CRE_Entity::getDepth()
{
	return posZ;
}

CRE_RenderingFlag CRE_Entity::getRenderingFlag()
{
	return renderingFlag;
}

void CRE_Entity::setRenderingFlag(CRE_RenderingFlag flag)
{
	renderingFlag = flag;

	eTexture.setRenderingFlag(flag);
}

void CRE_Entity::setEntityType(const CRE_EntityType& i)
{
	data.entityType = i;
}

CRE_EntityType CRE_Entity::getEntityType()
{
	return data.entityType;
}

SDL_Rect CRE_Entity::getTextureDest()
{
	return eTexture.getDestRect();
}

void CRE_Entity::updateAnimation()
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

			setTexture(*(eAnimation->textureData));
			eTexture.setRenderingFlag(renderingFlag);
		}

		animFrameCount--;
	}
}