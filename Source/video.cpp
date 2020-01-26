#include "video.h"
//#include <cassert>

#define FRAMECAP_60

extern SDL_Renderer* CRERenderer;
extern vector<entity*> entityBlock;
extern vector<entity*> background;
extern vector<entity*> foreground;


//flag to have only onscreen entites render to the image
#define ONSCREEN_RENDER_ONLY

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
	//clear the frame to blank for renderering
	SDL_RenderClear(CRERenderer);

	
	//loops through defined entities
	//addes defined entities to rendering queues depending on internal
	//rendering flags (SPRITE, BACKGROUND, FOREGROUND, etc)

	//temperary texture for renderering
	//use to place entities from rendering queue and to render to frame
	texture tempTexture;

	/***  Queue backgrounds to render based on depth  ***/
	int maxDepth = 0;

	for (unsigned int i = 0; i < background.size(); i++)
	{
		int tempPos[3];
		background[i]->getPosition(tempPos);
		if (tempPos[2] > maxDepth)
			maxDepth = tempPos[2];
	}

	int currentDepth = 0;

	while (currentDepth <= maxDepth)
	{
		for (unsigned int i = 0; i < background.size(); i++)
		{
			if (background[i]->getDepth() == currentDepth)
			{
				switch (background[i]->getRenderingFlag())
				{
				case RENDERINGFLAG_BACKGROUND: 
					backgroundQueue.push(background[i]->getTexture());
					break;
				case RENDERINGFLAG_STATIC_BACKGROUND:
					staticBackgroundQueue.push(background[i]->getTexture());
				default:
					break;
				}
			}
		}
		currentDepth++;
	}
	
	/***  Render queued backgrounds  ***/

	//Static backgrounds queued to allow paralax b.g.
	while (!staticBackgroundQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *staticBackgroundQueue.front();
		staticBackgroundQueue.pop();

		//render set up background layer for renderering.
		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
	}

	//Backgrounds queued to allow paralax b.g.
	while (!backgroundQueue.empty())
	{
		tempTexture = *backgroundQueue.front();
		backgroundQueue.pop();
		//load background layer from queue for renderering

		//unsure how to handle math for this

		//render set up background layer for renderering.
		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempTexture.getDestRect());
	}
	
	/***  Queue sprites to render based on depth ***/
	maxDepth = 0;

	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		int tempPos[3];
		entityBlock[i]->getPosition(tempPos);
		if (tempPos[2] > maxDepth)
			maxDepth = tempPos[2];
	}

	for(currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < entityBlock.size(); i++)
		{
			if (entityBlock[i]->getDepth() == currentDepth)
			{
				SDL_Rect tempDest = entityBlock[i]->getTextureDest();
				
#ifdef ONSCREEN_RENDER_ONLY
				//check if entity's texture is on screen
				if( tempDest.x < cameraPosX + screenWidth &&
				    tempDest.x + tempDest.w > cameraPosX &&
					tempDest.y < cameraPosY + screenHeight &&
					tempDest.y + tempDest.h > cameraPosY)
#endif //ONSCREEN_RENDER_ONLY
					spriteQueue.push(entityBlock[i]->getTexture());
			}
		}
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

		//render set up entity texture for renderering.
		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempRect);
	}

	/***  Queue foregrounds to render based on depth  ***/
	maxDepth = 0;

	for (unsigned int i = 0; i < foreground.size(); i++)
	{
		int tempPos[3];
		foreground[i]->getPosition(tempPos);
		if (tempPos[2] > maxDepth)
			maxDepth = tempPos[2];
	}

	currentDepth = 0;

	while (currentDepth <= maxDepth)
	{
		for (unsigned int i = 0; i < foreground.size(); i++)
		{
			if (foreground[i]->getDepth() == currentDepth)
			{
				switch (foreground[i]->getRenderingFlag())
				{
				case RENDERINGFLAG_FOREGROUND:
					foregroundQueue.push(foreground[i]->getTexture());
					break;
				case RENDERINGFLAG_STATIC_FOREGROUND:
					staticForegroundQueue.push(foreground[i]->getTexture());
				default:
					break;
				}
			}
		}
		currentDepth++;
	}

	/***  Render queued foregrounds ***/
	//Foregrounds queued to allow paralax f.g. or HUD.
	while (!foregroundQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *foregroundQueue.front();
		foregroundQueue.pop();
		
		//unsure how to handle math for this

		//render set up background layer for renderering.
		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &tempTexture.getDestRect());
	}

	//Static backgrounds queued to allow paralax b.g.
	while (!staticForegroundQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *staticForegroundQueue.front();
		staticForegroundQueue.pop();

		SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
		//render set up background layer for renderering.
	}

#ifdef FRAMECAP_60
	pollFrameTimer();
	setFrameTimer();
#endif

	//render frame to screen.
	SDL_RenderPresent(CRERenderer);
}

void video::loadTexture(texture* texture, RENDERINGFLAG flag)
{
	switch (flag)
	{
	case RENDERINGFLAG_SPRITE:
	default:
		spriteQueue.push(texture);
		break;

		//from here on need to edit implemetation of foregrounds and backgrounds
	case RENDERINGFLAG_BACKGROUND:
		//backgroundQueue.push(texture);
		break;
	case RENDERINGFLAG_FOREGROUND:
		//foregroundQueue.push(texture);
		break;
	case RENDERINGFLAG_STATIC_BACKGROUND:
		//staticBackgroundQueue.push(texture);
		break;
	case RENDERINGFLAG_STATIC_FOREGROUND:
		//staticForegroundQueue.push(texture);
		break;
	}
}