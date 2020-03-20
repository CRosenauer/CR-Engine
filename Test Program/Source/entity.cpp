#include "entity.h"

#include "video.h"
#include "config.h"

extern SDL_Renderer* CREInternalRenderer;
extern CRE_Video CREVideo;

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
	entityID = ++IDCounter;
}

CRE_Entity::~CRE_Entity()
{
	eTexture.~CRE_Texture();
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
	return eTexture.getRenderingFlag();
}

void CRE_Entity::setRenderingFlag(CRE_RenderingFlag flag)
{
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
			
			CRE_RenderingFlag renderingFlag = eTexture.getRenderingFlag();

			setTexture(*(eAnimation->textureData));

			eTexture.setRenderingFlag(renderingFlag);
		}

		animFrameCount--;
	}
}

void CRE_Entity::render()
{

	//variables for later use
	//destination rect of the entire image to draw
	SDL_Rect baseDest = eTexture.getDestRect();

	//destination rect of the image that will be rendered
	SDL_Rect onScreenDestRect;
	SDL_Rect viewportRect;
	
	CREVideo.getViewportRect(&viewportRect);

	float xScale = eTexture.getXScale();
	float yScale = eTexture.getYScale();

	double rotDegree = eTexture.getRotationDegree();
	SDL_RendererFlip flipFlag = eTexture.getFlipFlag();
	//printf("Flag flag: %i\n", flipFlag);

	//render set up entity texture for renderering.
	if (abs(rotDegree) < 0.05 && flipFlag == SDL_FLIP_NONE)
	{
		//no rotation and no flipping occurs

		//check if texture is scaled.
		if (!((xScale > 0.99 && xScale < 1.01) || (yScale > 0.99 && yScale < 1.01)))
		{
			//texture is scaled

			//math to scale texture
			baseDest.x += (1.0 - xScale) * baseDest.w / 2;
			baseDest.y += (1.0 - yScale) * baseDest.h / 2;
			baseDest.w *= xScale;
			baseDest.h *= yScale;

			//convert the position relative to the viewport
			baseDest.x = baseDest.x - viewportRect.x;
			baseDest.y = baseDest.y - viewportRect.y;

			if(SDL_RenderCopy(CREInternalRenderer, eTexture.getTexture(), &eTexture.getSourceRect(), &baseDest) != 0)
			{
				printf("Failed to render\nSDL_Error: %s\n", SDL_GetError());
			}

		}
		else
		{
			//texture is not scaled

			if (SDL_IntersectRect(&baseDest, &viewportRect, &onScreenDestRect))
			{
				SDL_Rect cutSource;

				//math to determine which part of the source image will be drawn from
				cutSource.x = onScreenDestRect.x - baseDest.x;
				cutSource.y = onScreenDestRect.y - baseDest.y;
				cutSource.w = onScreenDestRect.w;
				cutSource.h = onScreenDestRect.h;

				//convert the position relative to the viewport
				onScreenDestRect.x = onScreenDestRect.x - viewportRect.x;
				onScreenDestRect.y = onScreenDestRect.y - viewportRect.y;

				//render to screen
				if (SDL_RenderCopy(CREInternalRenderer, eTexture.getTexture(), &cutSource, &onScreenDestRect) != 0)
				{
					printf("Failed to render\nSDL_Error: %s\n", SDL_GetError());
				}
			}
		}
	}
	else
	{
		//rotation or flipping occurs

		if (!((xScale > 0.99 && xScale < 1.01) || (yScale > 0.99 && yScale < 1.01)))
		{
			//scale texture
			baseDest.x += (1.0 - xScale) * baseDest.w / 2;
			baseDest.y += (1.0 - yScale) * baseDest.h / 2;
			baseDest.w *= xScale;
			baseDest.h *= yScale;

			//covert texture position relative to viewport
			baseDest.x = baseDest.x - viewportRect.x;
			baseDest.y = baseDest.y - viewportRect.y;

			if (SDL_RenderCopyEx(CREInternalRenderer, eTexture.getTexture(), &eTexture.getSourceRect(), &baseDest,
				rotDegree, NULL, flipFlag) != 0)
			{
				printf("Failed to render\nSDL_Error: %s\n", SDL_GetError());
			}
		}
		else
		{
			//convert texture pos relative to viewport
			baseDest.x = baseDest.x - viewportRect.x;
			baseDest.y = baseDest.y - viewportRect.y;

			if(SDL_RenderCopyEx(CREInternalRenderer, eTexture.getTexture(), &eTexture.getSourceRect(), &baseDest,
				rotDegree, NULL, flipFlag) != 0)
			{
				printf("Failed to render\nSDL_Error: %s\n", SDL_GetError());
			}
		}
	}

	updateAnimation();
}