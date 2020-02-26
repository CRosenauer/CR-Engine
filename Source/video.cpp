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

	setFrameRate(DEAFULT_FRAME_RATE);
	setFrameTimer();
}

void CRE_Video::render()
{
	//clear the frame to blank for renderering
	SDL_RenderClear(CRERenderer);
	
	//loops through defined entities
	//addes defined entities to rendering queues depending on internal
	//rendering flags

	//temperary texture for renderering
	//use to place entities from rendering queue and to render to frame
	CRE_Texture tempTexture;

	/***  Queue backgrounds and foregrounds to render queues based on depth  ***/


	unsigned int maxDepth = 0;
	unsigned int currentDepth = 0;

	//find the maximum depth of the backgrounds
	for (unsigned int i = 0; i < background.size(); i++)
	{
		unsigned int finderDepth;
		finderDepth = background[i]->getDepth();

		if (finderDepth > maxDepth)
			maxDepth = finderDepth;
	}

	//push backgrounds to background rendering queue based on depth
	for (currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < background.size(); i++)
		{
			if (background[i]->getDepth() == currentDepth)
			{
				backgroundQueue.push(background[i]->getTexture());
				background[i]->update();
			}
		}
	}


	maxDepth = 0;
	currentDepth = 0;

	//find the maximum depth of the backgrounds
	for (unsigned int i = 0; i < foreground.size(); i++)
	{
		unsigned int finderDepth;
		finderDepth = foreground[i]->getDepth();

		if (finderDepth > maxDepth)
			maxDepth = finderDepth;
	}

	//push backgrounds to background rendering queue based on depth
	for (currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < foreground.size(); i++)
		{
			if (foreground[i]->getDepth() == currentDepth)
			{
				foregroundQueue.push(foreground[i]->getTexture());
				foreground[i]->update();
			}
		}
	}


	maxDepth = 0;
	currentDepth = 0;

	/***  Queue sprites to render based on depth ***/

	//find max depth of the entity's
	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		unsigned int finderDepth = entityBlock[i]->getDepth();

		if (finderDepth > maxDepth)
			maxDepth = finderDepth;
	}

	//queue entity's based on depth
	for(currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < entityBlock.size(); i++)
		{
			if (entityBlock[i]->getDepth() == currentDepth)
			{
				
				switch (entityBlock[i]->getRenderingFlag())
				{
				case RENDERINGFLAG_STATIC_BACKGROUND:
				case RENDERINGFLAG_BACKGROUND:
					backgroundQueue.push(entityBlock[i]->getTexture());
					break;
				default:
				case RENDERINGFLAG_SPRITE:
					spriteQueue.push(entityBlock[i]->getTexture());
					break;
				case RENDERINGFLAG_FOREGROUND:
				case RENDERINGFLAG_STATIC_FOREGROUND:
					foregroundQueue.push(entityBlock[i]->getTexture());
					break;
				}
				
				entityBlock[i]->updateAnimation();
			}
		}
	}



	/***  Render all queued textures  ***/

	/***  Render queued backgrounds  ***/

	//Backgrounds queued to allow paralax b.g.
	while (!backgroundQueue.empty())
	{
		tempTexture = *backgroundQueue.front();
		backgroundQueue.pop();


		//variables for later use

		//destination rect of the entire image to draw
		SDL_Rect baseDestTempRect = tempTexture.getDestRect(); 

		//destination rect of the image that will be rendered
		//altered in the following switch statement
		SDL_Rect onScreenDestRect;

		//rectangle which contains the viewport.
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, screenWidth, screenHeight }; //rect to represent viewport

		switch (tempTexture.getRenderingFlag())
		{

		default:
		case RENDERINGFLAG_BACKGROUND:
			//load background layer from queue for renderering

			//render set up entity texture for renderering.

			if (SDL_IntersectRect(&baseDestTempRect, &viewportRect, &onScreenDestRect))
			{
				//math to determine which part of the source image will be rendered
				//used to save performance with drawing
				SDL_Rect cutSource;

				//math to determine which part of the source rect will appear on screen
				//only draws from the part of the source rect that would appear on screen.
				cutSource.x = onScreenDestRect.x - baseDestTempRect.x;
				cutSource.y = onScreenDestRect.y - baseDestTempRect.y;
				cutSource.w = onScreenDestRect.w;
				cutSource.h = onScreenDestRect.h;

				//math to render relative to viewport position
				onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
				onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
			}

			break;
		//render textures who's position is relative to viewport position
		case RENDERINGFLAG_STATIC_BACKGROUND:
			//render set up background layer for renderering.
			if (baseDestTempRect.w <= 0 || baseDestTempRect.h <= 0)
			{
				//case destination rect is invalid. Assume fill screen
				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
			}
			else
			{
				//case destination rect is valid. Draws to texture's destination rect
				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDestTempRect);
			}
			break;
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

		//rect to represent viewport
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, screenWidth, screenHeight };

		//destination rect of the entire image to draw
		SDL_Rect baseDestTempRect = tempTexture.getDestRect();

		//destination rect of the image that will be rendered
		//altered in the following switch statement
		SDL_Rect onScreenDestRect;

		switch (tempTexture.getRenderingFlag())
		{
		default:
		case RENDERINGFLAG_FOREGROUND:
			//load background layer from queue for renderering

			

			//render set up entity texture for renderering.

			//
			if (SDL_IntersectRect(&baseDestTempRect, &viewportRect, &onScreenDestRect))
			{
				//math to determine which part of the source image will be rendered
				//used to save performance with drawing
				SDL_Rect cutSource;

				//math to determine which part of the source rect will appear on screen
				//only draws from the part of the source rect that would appear on screen.
				cutSource.x = onScreenDestRect.x - baseDestTempRect.x;
				cutSource.y = onScreenDestRect.y - baseDestTempRect.y;
				cutSource.w = onScreenDestRect.w;
				cutSource.h = onScreenDestRect.h;

				//math to render relative to viewport position
				onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
				onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
			}

			break;

			//render textures who's position is relative to viewport position
		case RENDERINGFLAG_STATIC_FOREGROUND:
			//render set up background layer for renderering.
			if (baseDestTempRect.w <= 0 || baseDestTempRect.h <= 0)
			{
				//case destination rect is invalid. Assume fill screen
				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
			}
			else
			{
				//case destination rect is valid. Draws to texture's destination rect
				SDL_RenderCopy(CRERenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDestTempRect);
			}

			break;
		}


		//old code. kept incase i mess something up.

		/*
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
		}*/
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