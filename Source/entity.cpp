#include "entity.h"

//vector for containing entities
vector<entity*> entityBlock;
vector<entity*> background;
vector<entity*> foreground;

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
		
		setTexture(eAnimation->textureData);
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

	if (z > 0)
		posZ = z;
	else
		posZ = 0;

	printf("Set Position:\nEntity ID: %i. Z Position: %i\n", entityID, posZ);

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