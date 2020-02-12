#include "ground.h"

vector<ground*> background;
vector<ground*> foreground;

ground::ground()
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

ground::ground(const groundData& data)
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

void ground::loadGround(const groundData& data)
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

void ground::update()
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

void setGround(const groundData& groundDat)
{
	printf("Stub: setGround in ground.cpp.\nTo be altered and improved upon later.\n");
	resetGround();

	const groundData* tempData = &groundDat;

	while (tempData != NULL)
	{
		switch (tempData->flag)
		{
		case RENDERINGFLAG_BACKGROUND:
		case RENDERINGFLAG_STATIC_BACKGROUND:
			background.push_back(new ground(*tempData));
			break;
		case RENDERINGFLAG_FOREGROUND:
		case RENDERINGFLAG_STATIC_FOREGROUND:
			foreground.push_back(new ground(*tempData));
		default:
			break;
		}

		tempData = tempData->next;
	}
}

void resetGround(const RENDERING_FLAG& flag)
{
	vector<ground*>::iterator itr;

	switch (flag)
	{
	case RENDERINGFLAG_FOREGROUND: 
	case RENDERINGFLAG_STATIC_FOREGROUND:
		for (itr = foreground.begin(); itr != foreground.end(); itr++)
		{
			if ((*itr)->getRenderingFlag() == flag)
			{
				itr = foreground.erase(itr);

				if (itr != foreground.begin())
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
				itr = background.erase(itr);

				if (itr != background.begin())
					itr--;
			}
		}

	default:
		break;
	}
}

void resetGround()
{
	//deallocate foregrounds
	for (unsigned int i = 0; i < foreground.size(); i++)
		delete foreground[i];
	foreground.clear();

	//deallocate backgrounds
	for (unsigned int i = 0; i < background.size(); i++)
		delete foreground[i];
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

void loadGround(const groundData& groundDat)
{

}