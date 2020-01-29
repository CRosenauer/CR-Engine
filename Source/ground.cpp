#include "ground.h"

vector<ground*> background;
vector<ground*> foreground;

ground::ground()
{
	posX = 0;
	posY = 0;
}

ground::ground(const groundData& data)
{
	posX = 0;
	posY = 0;

	renderingFlag = data.flag;

	imageType = data.imageType;

	switch (imageType)
	{
	deafult:
	case TEXTURE:
		gAnimation = NULL;
		destRect.w = data.data.text.source.w;
		destRect.h = data.data.text.source.h;
		destRect.x = posX;
		destRect.y = posY;
		gTexture.loadTexture(data.data.text, destRect);
		break;

	case ANIMATION:
		gAnimation = &data.data.animation;
		if (data.animFlag == ANIMATION_LOOP)
			gFirstAnim = gAnimation;
		else
			gFirstAnim = NULL;
		destRect.w = data.data.animation.textureData.source.w;
		destRect.h = data.data.animation.textureData.source.h;
		destRect.x = posX;
		destRect.y = posY;
		gTexture.loadTexture(data.data.animation.textureData, destRect);
		break;
	}
}

void ground::loadGround(const groundData& data)
{
	renderingFlag = data.flag;

	imageType = data.imageType;

	switch (imageType)
	{
	deafult:
	case TEXTURE:
		gAnimation = NULL;
		destRect.w = data.data.text.source.w;
		destRect.h = data.data.text.source.h;
		destRect.x = posX;
		destRect.y = posY;
		gTexture.loadTexture(data.data.text, destRect);
		break;

	case ANIMATION:
		gAnimation = &data.data.animation;
		if (data.animFlag == ANIMATION_LOOP)
			gFirstAnim = gAnimation;
		else
			gFirstAnim = NULL;
		destRect.w = data.data.animation.textureData.source.w;
		destRect.h = data.data.animation.textureData.source.h;
		destRect.x = posX;
		destRect.y = posY;
		gTexture.loadTexture(data.data.animation.textureData, destRect);
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
			}

			animFrameCount--;

			gTexture.loadTexture(gAnimation->textureData, destRect);
		}
	}
}

void setGround(const groundData& groundDat)
{

}

void resetGround(RENDERING_FLAG flag)
{

}

void updateGrounds()
{

}