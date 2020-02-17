#include "video.h"
//#include <cassert>

extern SDL_Renderer* CRERenderer;
extern vector<entity*> entityBlock;
extern vector<ground*> background;
extern vector<ground*> foreground;


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

	/***  Queue backgrounds and g=foregrounds to render queues based on depth  ***/
	for (unsigned int i = 0; i < background.size(); i++)
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

	for (unsigned int i = 0; i < foreground.size(); i++)
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


	//vars for holding information related to 
	int maxDepth = 0;
	int currentDepth = 0;

	/***  Queue sprites to render based on depth ***/
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
					switch (entityBlock[i]->getRenderingFlag())
					{
					case RENDERINGFLAG_STATIC_BACKGROUND:
						staticBackgroundQueue.push(entityBlock[i]->getTexture());
						break;
					case RENDERINGFLAG_BACKGROUND:
						backgroundQueue.push(entityBlock[i]->getTexture());
						break;
					default:
					case RENDERINGFLAG_SPRITE:
						spriteQueue.push(entityBlock[i]->getTexture());
						break;
					case RENDERINGFLAG_FOREGROUND:
						foregroundQueue.push(entityBlock[i]->getTexture());
						break;
					case RENDERINGFLAG_STATIC_FOREGROUND:
						staticForegroundQueue.push(entityBlock[i]->getTexture());
						break;
					}
				
				entityBlock[i]->updateAnimation();
			}
		}
	}

	/***  Render all queued textures  ***/


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


	/***  Render queued sprites  ***/
	while (!spriteQueue.empty())
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

	//update animations
	updateGrounds();
	//update entityAnim();


	//render frame to screen.
	SDL_RenderPresent(CRERenderer);

#ifdef FRAMECAP_60
	pollFrameTimer();
	setFrameTimer();
#endif

#ifdef FRAMERATE_COUNTER
	prevTicks = currentTicks;
	currentTicks = static_cast<float>(SDL_GetTicks());

	frameRate = 1000.f / (currentTicks - prevTicks);
	//printf("Frame rate: %f\n", frameRate);
#endif
}

void video::loadTexture(texture* texture, RENDERING_FLAG flag)
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

void video::getCameraPos(int pos[2])
{
	pos[0] = cameraPosX;
	pos[1] = cameraPosY;
}

void video::setCameraPos(const int pos[2])
{
	cameraPosX = pos[0];
	cameraPosY = pos[1];
}

#ifdef FRAMERATE_COUNTER
float video::getFrameRate()
{
	return frameRate;
}
#endif