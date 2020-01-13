#include "video.h"
#include <cassert>

extern SDL_Renderer* CRERenderer;

video::video()
{
	title =  "Test Game";
	screenWidth = 640;
	screenHeight = 480;
	cameraPosX = 0;
	cameraPosY = 0;
	windowFlag = SDL_WINDOW_SHOWN;

	CREVWindow = NULL;
	CREVSurface = NULL;
}

video::video(const std::string& TITLE , const int& SCREENWIDTH, const int& SCREENHEIGHT, const Uint32& WINDOWFLAG)
{
	title = TITLE;
	screenWidth = SCREENWIDTH;
	screenHeight = SCREENHEIGHT;
	cameraPosX = 0;
	cameraPosY = 0;
	windowFlag = WINDOWFLAG;

	CREVWindow = NULL;
	CREVSurface = NULL;
}

void video::init()
{
	CREVWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, windowFlag);
	if (CREVWindow == NULL)
	{
		printf("Window cannot be created.\nError: %s", SDL_GetError());
		exit(-1);
	}

	//associates gSurface with the rendering window
	CREVSurface = SDL_GetWindowSurface(CREVWindow);
	if (CREVSurface == NULL)
	{
		printf("Video surface cannot be loaded to assigned from window.\nError: %s", SDL_GetError());
		exit(-1);
	}

	CRERenderer = SDL_CreateRenderer(CREVWindow, -1, SDL_RENDERER_ACCELERATED);
	if (CRERenderer == NULL)
	{
		printf("Renderer cannot be established. Error: %s", SDL_GetError());
		exit(-1);
	}

	setFrameRate(60);
	setFrameTimer();
}

void video::render()
{
	SDL_RenderClear(CRERenderer);
	//clear the frame to blank for renderering

	//TODO: implement depth based rendering priority

	//fix no change bug
	//loops through defined entities
	//addes defined entities to rendering queues depending on internal
	//rendering flags (SPRITE, BACKGROUND, FOREGROUND, etc)

	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		switch (entityBlock[i]->getRenderingFlag())
		{
		case RENDERINGFLAG_SPRITE:
		default:
			spriteQueue.push(entityBlock[i]->getTexture());
			break;
		case RENDERINGFLAG_BACKGROUND:
			backgroundQueue.push(entityBlock[i]->getTexture());
			break;
		case RENDERINGFLAG_FOREGROUND:
			foregroundQueue.push(entityBlock[i]->getTexture());
			break;
		}
	}

	//temperary texture for renderering
	//use to place entities from rendering queue and to render to frame
	texture tempTexture;

	/***  Render queued backgrounds  ***/
	//Backgrounds queued to allow paralax b.g.
	while (!backgroundQueue.empty())
	{
		tempTexture = *backgroundQueue.front();
		backgroundQueue.pop();
		//load background layer from queue for renderering

		//unsure how to handle math for this

		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempTexture.getDestRect());
		//render set up background layer for renderering.
	}

	/***  Render queued sprites  ***/
	while(!spriteQueue.empty())
	{
		tempTexture = *spriteQueue.front();

		spriteQueue.pop();

		//load entity from entity rendering queue
		//and pop front element from queue
		
		SDL_Rect tempRect = tempTexture.getDestRect();

		tempRect.x = tempRect.x - cameraPosX;
		tempRect.y = tempRect.y - cameraPosY;

		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempRect);
		//render set up entity texture for renderering.
	}

	/***  Render queued foregrounds  ***/
	//Foregrounds queued to allow paralax f.g. or HUD.
	while (!foregroundQueue.empty())
	{
		tempTexture = *foregroundQueue.front();
		foregroundQueue.pop();
		//load background layer from queue for renderering

		//unsure how to handle math for this

		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempTexture.getDestRect());
		//render set up background layer for renderering.
	}

	pollFrameTimer();
	setFrameTimer();

	SDL_RenderPresent(CRERenderer);
	//render frame to screen.
}


void video::loadTexture(texture* texture, CREVRenderingFlag flag)
{
	switch (flag)
	{
	case RENDERINGFLAG_SPRITE:
	default:
		spriteQueue.push(texture);
		break;
	case RENDERINGFLAG_BACKGROUND:
		foregroundQueue.push(texture);
		break;
	case RENDERINGFLAG_FOREGROUND:
		backgroundQueue.push(texture);
		break;
	}
}