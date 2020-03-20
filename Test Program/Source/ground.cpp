#include "ground.h"

#include "video.h"
extern SDL_Renderer* CREInternalRenderer;
extern CRE_Video CREVideo;

vector<CRE_Ground*> background;
vector<CRE_Ground*> foreground;

CRE_Ground::CRE_Ground()
{
	posX = 0;
	posY = 0;
	animFrameCount = 0;
	gAnimation = NULL;
	gFirstAnim = NULL;
	imageType = TEXTURE;
	posZ = 0;
	renderingFlag = RENDERINGFLAG_BACKGROUND;
}

CRE_Ground::CRE_Ground(const CRE_GroundData& data)
{
	posX = 0;
	posY = 0;
	posZ = data.groundDepth;

	renderingFlag = data.flag;

	imageType = data.imageType;

	switch (imageType)
	{
	default:
	case TEXTURE:
		//set animation related data to NULL
		gAnimation = NULL;
		gFirstAnim = NULL;
		animFrameCount = 0;

		//set rendering information from passed groundData struct
		destRect.w = data.data->text->source.w;
		destRect.h = data.data->text->source.h;
		destRect.x = posX;
		destRect.y = posY;
		
		//load texture from groundData struct
		gTexture.loadTexture(*(data.data->text), destRect);
		gTexture.setRenderingFlag(renderingFlag);
		break;

	case ANIMATION:
		//set animation information from groundData struct
		gAnimation = data.data->anim;
		if (data.animFlag == ANIMATION_LOOP)
			gFirstAnim = gAnimation;
		else
			gFirstAnim = NULL;
		animFrameCount = 0;

		//set rendering destination for passed groundData struct
		destRect.w = data.data->anim->textureData->source.w;
		destRect.h = data.data->anim->textureData->source.h;
		destRect.x = posX;
		destRect.y = posY;

		//load first frame from the animation.
		gTexture.loadTexture(*(data.data->anim->textureData), destRect);
		gTexture.setRenderingFlag(renderingFlag);
		break;
	}
}

CRE_Ground::~CRE_Ground()
{
	gTexture.~CRE_Texture();
	gAnimation = NULL;
	gFirstAnim = NULL;
}

void CRE_Ground::loadGround(const CRE_GroundData& data)
{
	posX = 0;
	posY = 0;
	posZ = data.groundDepth;

	renderingFlag = data.flag;

	imageType = data.imageType;

	switch (imageType)
	{
	default:
	case TEXTURE:
		//set animation related data to NULL
		gAnimation = NULL;
		gFirstAnim = NULL;
		animFrameCount = 0;

		//set rendering information from passed groundData struct
		destRect.w = data.data->text->source.w;
		destRect.h = data.data->text->source.h;
		destRect.x = posX;
		destRect.y = posY;

		//load texture from groundData struct
		gTexture.loadTexture(*(data.data->text), destRect);

		gTexture.setRenderingFlag(renderingFlag);

		break;

	case ANIMATION:
		//set animation information from groundData struct
		gAnimation = data.data->anim;
		if (data.animFlag == ANIMATION_LOOP)
			gFirstAnim = gAnimation;
		else
			gFirstAnim = NULL;
		animFrameCount = 0;

		//set rendering destination for passed groundData struct
		destRect.w = data.data->anim->textureData->source.w;
		destRect.h = data.data->anim->textureData->source.h;
		destRect.x = posX;
		destRect.y = posY;

		//load first frame from the animation.
		gTexture.loadTexture(*(data.data->anim->textureData), destRect);
		gTexture.setRenderingFlag(renderingFlag);
		break;
	}
}

void CRE_Ground::updateAnimation()
{
	if (imageType == ANIMATION)
	{
		if (gAnimation != NULL)
		{

			//checks for animation frame count, cycles to the next frame of animation.
			if (animFrameCount == 0)
			{
				//checks if there is a next frame in the animation.
				if (gAnimation->nextFrame == NULL)
				{
					//checks for looping animation. if looping animation then
					//cycles to the next (first) frame of animation
					if (gFirstAnim != NULL)
					{
						gAnimation = gFirstAnim;
						animFrameCount = gAnimation->frameCount;
					}
				}
				else
				{
					gAnimation = gAnimation->nextFrame;
					animFrameCount = gAnimation->frameCount;
				}

				gTexture.loadTexture(*(gAnimation->textureData), destRect);
				gTexture.setRenderingFlag(renderingFlag);
			}

			animFrameCount--;
		}
	}
}

void CRE_Ground::setScale(const float& x, const float& y)
{
	gTexture.setXScale(x);
	gTexture.setYScale(y);
}

void CRE_Ground::getScale(float scale[2])
{
	scale[0] = gTexture.getXScale();
	scale[1] = gTexture.getYScale();
}

void CRE_Ground::render()
{
	//destination rect of the entire image to draw
	SDL_Rect baseDest = gTexture.getDestRect();

	//destination rect of the image that will be rendered
	SDL_Rect onScreenDestRect;
	SDL_Rect viewportRect; //rect to represent viewport
	CREVideo.getViewportRect(&viewportRect);

	switch (gTexture.getRenderingFlag())
	{
	default:
	case RENDERINGFLAG_FOREGROUND:
	case RENDERINGFLAG_BACKGROUND:
		//load background layer from queue for renderering

		//render set up entity texture for renderering.

		//math to only render portion of the background that is onscreen.
		//load background layer from queue for renderering

		//render set up entity texture for renderering.

		//
		if (SDL_IntersectRect(&baseDest, &viewportRect, &onScreenDestRect))
		{
			//math to determine which part of the source image will be rendered
			//used to save performance with drawing
			SDL_Rect cutSource;

			//math to determine which part of the source rect will appear on screen
			//only draws from the part of the source rect that would appear on screen.
			cutSource.x = onScreenDestRect.x - baseDest.x;
			cutSource.y = onScreenDestRect.y - baseDest.y;
			cutSource.w = onScreenDestRect.w;
			cutSource.h = onScreenDestRect.h;

			//math to render relative to viewport position
			onScreenDestRect.x = onScreenDestRect.x - viewportRect.x;  //convert the position relative to the viewport
			onScreenDestRect.y = onScreenDestRect.y - viewportRect.y;

			SDL_RenderCopy(CREInternalRenderer, gTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
		}

		break;

		//render textures who's position is relative to viewport position
	case RENDERINGFLAG_STATIC_FOREGROUND:
	case RENDERINGFLAG_STATIC_BACKGROUND:
		//render set up background layer for renderering.
		if (baseDest.w <= 0 || baseDest.h <= 0)
		{
			//case destination rect is invalid. Assume fill screen
			SDL_RenderCopy(CREInternalRenderer, gTexture.getTexture(), &gTexture.getSourceRect(), NULL);
		}
		else
		{
			//case destination rect is valid. Draws to texture's destination rect
			SDL_RenderCopy(CREInternalRenderer, gTexture.getTexture(), &gTexture.getSourceRect(), &baseDest);
		}

		break;
	}

	updateAnimation();
}

void setGround(const CRE_GroundData& groundDat)
{
	resetGround();
	loadGround(groundDat);
}

void resetGround(const CRE_RenderingFlag& flag)
{
	vector<CRE_Ground*>::iterator itr;

	switch (flag)
	{
	case RENDERINGFLAG_FOREGROUND:
	case RENDERINGFLAG_STATIC_FOREGROUND:
		for (itr = foreground.begin(); itr != foreground.end(); itr++)
		{
			if ((*itr)->getRenderingFlag() == flag)
			{
				foreground.erase(itr);

				if (foreground.empty())
					break;

				if(itr != foreground.begin())
					itr--;
			}
		}
		break;

	case RENDERINGFLAG_BACKGROUND:
	case RENDERINGFLAG_STATIC_BACKGROUND:
		for (itr = background.begin(); itr != background.end(); itr++)
		{
			if ((*itr)->getRenderingFlag() == flag)
			{
				background.erase(itr);

				if (background.empty())
					break;

				if( itr != background.begin())
					itr--;
			}
		}
	default:
		break;
	}
}

void resetGround()
{
	for (unsigned int i = 0; i < foreground.size(); i++)
	{
		foreground[i]->~CRE_Ground();
	}

	for (unsigned int i = 0; i < background.size(); i++)
	{
		background[i]->~CRE_Ground();
	}

	foreground.clear();
	background.clear();
}

void updateGrounds()
{
	for (unsigned int i = 0; i < foreground.size(); i++)
	{
		foreground[i]->updateAnimation();
	}

	for (unsigned int i = 0; i < background.size(); i++)
	{
		background[i]->updateAnimation();
	}
}

bool groundsEmpty()
{
	return foreground.empty() && background.empty();
}

void loadGround(const CRE_GroundData& groundDat)
{
	const CRE_GroundData* tempData = &groundDat;

	while (tempData != NULL)
	{
		switch (tempData->flag)
		{
		case RENDERINGFLAG_BACKGROUND:
		case RENDERINGFLAG_STATIC_BACKGROUND:
			background.push_back(new CRE_Ground(*tempData));
			break;
		case RENDERINGFLAG_FOREGROUND:
		case RENDERINGFLAG_STATIC_FOREGROUND:
			foreground.push_back(new CRE_Ground(*tempData));
		default:
			break;
		}

		tempData = tempData->next;
	}
}