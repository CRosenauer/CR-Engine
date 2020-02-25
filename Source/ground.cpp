#include "ground.h"

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
		break;
	}
}

void CRE_Ground::update()
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
			}

			animFrameCount--;
		}
	}
}

void setGround(const CRE_GroundData& groundDat)
{
	printf("Stub: setGround in ground.cpp.\nTo be altered and improved upon later.\n");
	resetGround();

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
		foreground[i]->update();
	}

	for (unsigned int i = 0; i < background.size(); i++)
	{
		background[i]->update();
	}
}

bool groundsEmpty()
{
	return foreground.empty() && background.empty();
}

void loadGround(const CRE_GroundData& groundDat)
{

}