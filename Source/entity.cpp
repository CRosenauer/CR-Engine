#include "entity.h"

//vector for containing entities
extern vector<entity*> entityBlock;

static unsigned int IDCounter = 0;

entity::entity()
{
	posX = 0;
	posY = 0;
	posZ = 0;
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

void deleteEntity(const unsigned int& entityID)
{
	//cycles through entityBus until an entity is found with the passed ID
	//entity with that id is then deallocated from memory and removed from entityBlock.
	for (vector<entity*>::iterator itr = entityBlock.begin(); itr < entityBlock.end(); itr++)
	{
		if (entityID == (*itr)->getEntityID())
		{
			delete* itr;

			entityBlock.erase(itr);
			break;
		}
	}
}

unsigned int allocateEntity()
{
	//allocates memory to a new entity in entityBlock
	//then returns the ID of the allocated ID
	entityBlock.push_back(new entity);

	return entityBlock.back()->getEntityID();
}

entity* entityFromID(const unsigned int& id)
{
	//cycles through entityBlock until an entity is found whose internal ID
	//equals the passed ID. A pointer to this entity is returned.
	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		if (id == entityBlock[i]->getEntityID())
			return entityBlock[i];
	}

	//Case for if no entity with the passed ID can be found.
	//Will return NULL in this case.
	return NULL;
}