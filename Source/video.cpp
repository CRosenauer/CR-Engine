#include "video.h"

extern SDL_Renderer* CRERenderer;
extern vector<CRE_Entity*> entityBlock;
extern vector<CRE_Ground*> background;
extern vector<CRE_Ground*> foreground;

CRE_Video::CRE_Video()
{
	title =  "Test Game";
	screenWidth = RENDERING_SCREEN_WIDTH;
	screenHeight = RENDERING_SCREEN_HEIGHT;
	cameraPosX = 0;
	cameraPosY = 0;
	windowFlag = SDL_WINDOW_SHOWN;

	CREVWindow = NULL;
	CREVSurface = NULL;
}

CRE_Video::CRE_Video(const std::string& TITLE , const int& SCREENWIDTH, const int& SCREENHEIGHT, const Uint32& WINDOWFLAG)
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

void CRE_Video::init()
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

void CRE_Video::render()
{
	//clear the frame to blank for renderering
	SDL_RenderClear(CRERenderer);
	
	//loops through defined entities
	//addes defined entities to rendering queues depending on internal
	//rendering flags (SPRITE, BACKGROUND, FOREGROUND, etc)

	//temperary texture for renderering
	//use to place entities from rendering queue and to render to frame
	CRE_Texture tempTexture;

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

		//variables for later use
		SDL_Rect baseDestTempRect = tempTexture.getDestRect(); //destination rect of the entire image to draw
		SDL_Rect onScreenDestRect;							       //destination rect of the image that will be rendered
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, screenWidth, screenHeight }; //rect to represent viewport

		//render set up entity texture for renderering.
		if (SDL_IntersectRect(&baseDestTempRect, &viewportRect, &onScreenDestRect))
		{
			//math to determine which part of the source image will be rendered
			//used to save performance with drawing
			SDL_Rect cutSource;
			//destTempRect; //rect for what part of the source will be drawn

			//int dx = cutSource.x - baseDestTempRect.x;
			//int dy = cutSource.y - baseDestTempRect.y;

			cutSource.x = onScreenDestRect.x - baseDestTempRect.x;
			cutSource.y = onScreenDestRect.y - baseDestTempRect.y;
			cutSource.w = onScreenDestRect.w;
			cutSource.h = onScreenDestRect.h;

			// math to render relative to viewport position
			onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
			onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

			SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
		}
	}


	/***  Render queued sprites  ***/
	while (!spriteQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *spriteQueue.front();
		spriteQueue.pop();

		//variables for later use
		SDL_Rect baseDestTempRect = tempTexture.getDestRect(); //destination rect of the entire image to draw
		SDL_Rect onScreenDestRect;							       //destination rect of the image that will be rendered
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, screenWidth, screenHeight }; //rect to represent viewport

		//render set up entity texture for renderering.
		if (SDL_IntersectRect(&baseDestTempRect, &viewportRect, &onScreenDestRect))
		{
			//math to determine which part of the source image will be rendered
			//used to save performance with drawing
			SDL_Rect cutSource;
			//destTempRect; //rect for what part of the source will be drawn

			//int dx = cutSource.x - baseDestTempRect.x;
			//int dy = cutSource.y - baseDestTempRect.y;

			cutSource.x = onScreenDestRect.x - baseDestTempRect.x;
			cutSource.y = onScreenDestRect.y - baseDestTempRect.y;
			cutSource.w = onScreenDestRect.w;
			cutSource.h = onScreenDestRect.h;

			// math to render relative to viewport position
			onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
			onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

			SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
		}
	}


	/***  Render queued foregrounds ***/
	//Foregrounds queued to allow paralax f.g. or HUD.
	while (!foregroundQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *foregroundQueue.front();
		foregroundQueue.pop();
		
		//variables for later use
		SDL_Rect baseDestTempRect = tempTexture.getDestRect(); //destination rect of the entire image to draw
		SDL_Rect onScreenDestRect;							       //destination rect of the image that will be rendered
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, screenWidth, screenHeight }; //rect to represent viewport

		//render set up entity texture for renderering.
		if (SDL_IntersectRect(&baseDestTempRect, &viewportRect, &onScreenDestRect))
		{
			//math to determine which part of the source image will be rendered
			//used to save performance with drawing
			SDL_Rect cutSource;
			//destTempRect; //rect for what part of the source will be drawn

			//int dx = cutSource.x - baseDestTempRect.x;
			//int dy = cutSource.y - baseDestTempRect.y;

			cutSource.x = onScreenDestRect.x - baseDestTempRect.x;
			cutSource.y = onScreenDestRect.y - baseDestTempRect.y;
			cutSource.w = onScreenDestRect.w;
			cutSource.h = onScreenDestRect.h;

			// math to render relative to viewport position
			onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
			onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

			SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
		}
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

#ifdef FRAMECAP
	pollFrameTimer();
	setFrameTimer();
#endif
}

void CRE_Video::loadTexture(CRE_Texture* texture, CRE_RenderingFlag flag)
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

void CRE_Video::getCameraPos(int pos[2])
{
	pos[0] = cameraPosX;
	pos[1] = cameraPosY;
}

void CRE_Video::setCameraPos(const int pos[2])
{
	cameraPosX = pos[0];
	cameraPosY = pos[1];
}

void CRE_Video::getResolution(int pos[2])
{
	pos[0] = screenWidth;
	pos[1] = screenHeight;
}

#ifdef FRAMERATE_COUNTER
float video::getFrameRate()
{
	return frameRate;
}
#endif