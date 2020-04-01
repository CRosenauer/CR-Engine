#include "video.h"

extern SDL_Renderer* CREInternalRenderer;
extern vector<CRE_Entity*> entityBlock;
extern vector<CRE_Ground*> background;
extern vector<CRE_Ground*> foreground;

CRE_Video::CRE_Video()
{
	cameraPosX = 0;
	cameraPosY = 0;
	windowFlag = SDL_WINDOW_SHOWN;

	CREVWindow = NULL;
	CREVSurface = NULL;
}

void CRE_Video::init()
{
	CREVWindow = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowResolutionX,
		windowResolutionY,
		DEFAULT_FULLSCREEN_MODE);

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

	CREInternalRenderer = SDL_CreateRenderer(CREVWindow, -1, SDL_RENDERER_ACCELERATED);
	if (CREInternalRenderer == NULL)
	{
		printf("Renderer cannot be established. Error: %s", SDL_GetError());
		//exit(-1);
	}

	setScaleMode(DEFAULT_SCALE_MODE);

	setFrameRate(DEAFULT_FRAME_RATE);
	setFrameTimer();
}

void CRE_Video::render()
{
	//clear the frame to blank for renderering
	SDL_RenderClear(CREInternalRenderer);
	
	//loops through defined entities
	//addes defined entities to rendering queues depending on internal
	//rendering flags

	/*
	//temperary texture for renderering
	//use to place entities from rendering queue and to render to frame
	CRE_Texture tempTexture;


	//union and vectors to allow for entities and grounds to be interlaced in forebround and background
	//layers. Allows for interlaced depth-based rendering.
	
	/***  Queue backgrounds and foregrounds to render queues based on depth  ***/

	/*
	unsigned int maxDepth = 0;
	unsigned int currentDepth = 0;



	//find the maximum depth of the backgrounds
	/*
	for (unsigned int i = 0; i < background.size(); i++)
	{
		unsigned int finderDepth;
		finderDepth = background[i]->getDepth();

		if (finderDepth > maxDepth)
			maxDepth = finderDepth;
	}

	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		unsigned int finderDepth = entityBlock[i]->getDepth();

		if (finderDepth > maxDepth && 
			( entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_BACKGROUND ||
			entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_STATIC_BACKGROUND ))

			maxDepth = finderDepth;
	}*/
	/*
	Uint32 timer = SDL_GetTicks();

	//push backgrounds to background rendering queue based on depth
	for (currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < background.size() || i < entityBlock.size(); i++)
		{
			if(i < background.size())
				if (background[i]->getDepth() == currentDepth)
				{
					backgroundQueue.push(background[i]->getTexture());
				}

			if( i < entityBlock.size())
				if (entityBlock[i]->getDepth() == currentDepth && (
					entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_BACKGROUND ||
					entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_STATIC_BACKGROUND))
				{
					backgroundQueue.push(entityBlock[i]->getTexture());
					entityBlock[i]->updateAnimation();
				}
		}
	}


	maxDepth = 0;
	currentDepth = 0;

	//find the maximum depth of the foregrounds
	/*
	for (unsigned int i = 0; i < foreground.size(); i++)
	{
		unsigned int finderDepth;
		finderDepth = foreground[i]->getDepth();

		if (finderDepth > maxDepth)
			maxDepth = finderDepth;
	}

	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		unsigned int finderDepth = entityBlock[i]->getDepth();

		if (finderDepth > maxDepth &&
			(entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_FOREGROUND ||
			entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_STATIC_FOREGROUND))

			maxDepth = finderDepth;
	}*/
	/*
	//push foreground textures to foreground rendering queue
	for (currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < foreground.size() || i < entityBlock.size(); i++)
		{
			if (i < foreground.size())
				if (foreground[i]->getDepth() == currentDepth)
				{
					foregroundQueue.push(foreground[i]->getTexture());
				}

			if (i < entityBlock.size())
				if (entityBlock[i]->getDepth() == currentDepth &&
					(entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_FOREGROUND ||
					entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_STATIC_FOREGROUND))
				{
					foregroundQueue.push(entityBlock[i]->getTexture());
					entityBlock[i]->updateAnimation();
				}
		}
	}


	maxDepth = 0;
	currentDepth = 0;

	/***  Queue sprites to render based on depth ***/

	//find max depth of the entity's
	/*
	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		unsigned int finderDepth = entityBlock[i]->getDepth();

		if (finderDepth > maxDepth && entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_SPRITE)
			maxDepth = finderDepth;
	}*/
	/*
	//queue entity's based on depth
	for(currentDepth = 0; currentDepth <= maxDepth; currentDepth++)
	{
		for (unsigned int i = 0; i < entityBlock.size(); i++)
		{
			if (entityBlock[i]->getDepth() == currentDepth &&
				entityBlock[i]->getRenderingFlag() == RENDERINGFLAG_SPRITE)
			{
				spriteQueue.push(entityBlock[i]->getTexture());
				entityBlock[i]->updateAnimation();
			}
		}
	}

	printf("Time for texture queue loading: %i\n", SDL_GetTicks() - timer);
	timer = SDL_GetTicks();


	/***  Render all queued textures  ***/

	/***  Render queued backgrounds  ***/
/*
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
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, RENDERING_SCREEN_WIDTH, RENDERING_SCREEN_HEIGHT }; //rect to represent viewport

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

				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
			}

			break;
		//render textures who's position is relative to viewport position
		case RENDERINGFLAG_STATIC_BACKGROUND:
			//render set up background layer for renderering.
			if (baseDestTempRect.w <= 0 || baseDestTempRect.h <= 0)
			{
				//case destination rect is invalid. Assume fill screen
				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
			}
			else
			{
				//case destination rect is valid. Draws to texture's destination rect
				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDestTempRect);
			}
			break;
		}
		
		
	}
	/*
	/***  Render queued sprites  ***//*
	while (!spriteQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *spriteQueue.front();
		spriteQueue.pop();

		//variables for later use
		//destination rect of the entire image to draw
		SDL_Rect baseDest = tempTexture.getDestRect();

		//destination rect of the image that will be rendered
		SDL_Rect onScreenDestRect;							       
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, RENDERING_SCREEN_WIDTH, RENDERING_SCREEN_HEIGHT }; //rect to represent viewport

		float xScale = tempTexture.getXScale();
		float yScale = tempTexture.getYScale();

		double rotDegree = tempTexture.getRotationDegree();
		SDL_RendererFlip flipFlag = tempTexture.getFlipFlag();
		//printf("Flag flag: %i\n", flipFlag);

		//render set up entity texture for renderering.
		if(abs(rotDegree) < 0.05 && flipFlag == SDL_FLIP_NONE)
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
				baseDest.x = baseDest.x - cameraPosX;
				baseDest.y = baseDest.y - cameraPosY;

				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDest);

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
					onScreenDestRect.x = onScreenDestRect.x - cameraPosX;
					onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

					//render to screen
					SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); 
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
				baseDest.x = baseDest.x - cameraPosX;
				baseDest.y = baseDest.y - cameraPosY;

				SDL_RenderCopyEx(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDest,
					rotDegree, NULL, flipFlag);
			}
			else
			{
				//convert texture pos relative to viewport
				baseDest.x = baseDest.x - cameraPosX;
				baseDest.y = baseDest.y - cameraPosY;

				SDL_RenderCopyEx(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDest,
					rotDegree, NULL, flipFlag);
			}
		}
	}


	/***  Render queued foregrounds ***//*
	//Foregrounds queued to allow paralax f.g. or HUD.
	while (!foregroundQueue.empty())
	{
		//load background layer from queue for renderering
		tempTexture = *foregroundQueue.front();
		foregroundQueue.pop();
		
		//variables for later use

		//destination rect of the entire image to draw
		SDL_Rect baseDest = tempTexture.getDestRect();

		//destination rect of the image that will be rendered
		SDL_Rect onScreenDestRect;
		SDL_Rect viewportRect = { cameraPosX, cameraPosY, RENDERING_SCREEN_WIDTH, RENDERING_SCREEN_HEIGHT }; //rect to represent viewport

		switch (tempTexture.getRenderingFlag())
		{
		default:
		case RENDERINGFLAG_FOREGROUND:
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
				onScreenDestRect.x = onScreenDestRect.x - cameraPosX;  //convert the position relative to the viewport
				onScreenDestRect.y = onScreenDestRect.y - cameraPosY;

				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &cutSource, &onScreenDestRect); //render to screen
			}

			break;

			//render textures who's position is relative to viewport position
		case RENDERINGFLAG_STATIC_FOREGROUND:
			//render set up background layer for renderering.
			if (baseDest.w <= 0 || baseDest.h <= 0)
			{
				//case destination rect is invalid. Assume fill screen
				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), NULL);
			}
			else
			{
				//case destination rect is valid. Draws to texture's destination rect
				SDL_RenderCopy(CREInternalRenderer, tempTexture.getTexture(), &tempTexture.getSourceRect(), &baseDest);
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
		}*//*
	}
	
	*/

	int entityIndex  = 0;
	int groundsIndex = 0;
	int entitySize   = entityBlock.size();
	int groundsSize  = background.size();

	while (true)
	{
		if (groundsIndex >= groundsSize)
		{
			break;
		}

		while (*entityBlock[entityIndex] < *background[groundsIndex])
		{
			entityBlock[entityIndex]->render();
			entityIndex++;
		}

		background[groundsIndex]->render();
		groundsIndex++;
	}

	groundsSize  = foreground.size();
	groundsIndex = 0;

	while (true)
	{
		if (groundsIndex >= groundsSize)
		{
			break;
		}

		while (*entityBlock[entityIndex] < *foreground[groundsIndex])
		{
			entityBlock[entityIndex]->render();
			entityIndex++;
		}

		foreground[groundsIndex]->render();
		groundsIndex++;
	}

	for (; entityIndex < entitySize; entityIndex++)
	{
		entityBlock[entityIndex]->render();
	}
	

	/*
	for (int i = 0; i < background.size(); i++)
	{
		background[i]->render();
	}

	for (int i = 0; i < entityBlock.size(); i++)
	{
		
	}

	for (int i = 0; i < foreground.size(); i++)
	{
		foreground[i]->render();
	}*/

	//render frame to screen.
	SDL_RenderPresent(CREInternalRenderer);

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

void CRE_Video::setResolution(const int& width, const int& height)
{
	if (width <= 0 || height <= 0)
		return;

	windowResolutionX = width;
	windowResolutionY = height;

	float w = width;
	float h = height;

	windowXScale = w / RENDERING_SCREEN_WIDTH;
	windowYScale = h / RENDERING_SCREEN_HEIGHT;

	SDL_Rect displayRect = {0, 0, 0, 0};

	switch (scaleMode)
	{
	case CRE_SCALE_TO_FIT:
	default:

		//special case for windowed more to prevent black bars on the size of the window.
		if (fullscreenFlag == CRE_DISPLAY_WINDOWED)
		{

			SDL_RenderSetClipRect(CREInternalRenderer, NULL);
			SDL_RenderSetLogicalSize(CREInternalRenderer, 0, 0);

			if (windowXScale > windowYScale)
			{
				SDL_RenderSetScale(CREInternalRenderer, windowYScale, windowYScale);
				SDL_SetWindowSize(CREVWindow, RENDERING_SCREEN_WIDTH * windowYScale, RENDERING_SCREEN_HEIGHT * windowYScale);
			}
			else
			{
				SDL_RenderSetScale(CREInternalRenderer, windowXScale, windowXScale);
				SDL_SetWindowSize(CREVWindow, RENDERING_SCREEN_WIDTH * windowXScale, RENDERING_SCREEN_HEIGHT * windowXScale);
			}
		}
		else
		{
			//math to determine which area of the window will have graphics

			//likely wrong
			w = windowXScale * RENDERING_SCREEN_WIDTH;
			h = windowYScale * RENDERING_SCREEN_HEIGHT;

			displayRect.w = w;
			displayRect.h = h;
			displayRect.y = (height - h) / 2;
			displayRect.x = (width - w) / 2;

			//reset scaling
			int i = SDL_RenderSetScale(CREInternalRenderer, 0, 0);

			SDL_RenderSetLogicalSize(CREInternalRenderer, RENDERING_SCREEN_WIDTH, RENDERING_SCREEN_HEIGHT);

			//ensure graphics are only being displayed within the display window (not on black bars).
			SDL_RenderSetClipRect(CREInternalRenderer, &displayRect);

			SDL_SetWindowSize(CREVWindow, width, height);
		}

		break;

	case CRE_STRETCH_TO_FIT:
		//reset logical size
		SDL_RenderSetLogicalSize(CREInternalRenderer, 0, 0);

		SDL_RenderSetScale(CREInternalRenderer, windowXScale, windowYScale);

		//render everything that appears in the window
		SDL_RenderSetClipRect(CREInternalRenderer, NULL);

		SDL_SetWindowSize(CREVWindow, width, height);
		break;
	}

	//resize window and center it in the screen
	//SDL_SetWindowSize(CREVWindow, width, height);
	SDL_SetWindowPosition(CREVWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void CRE_Video::setFullscreenMode(const CRE_Fullscreen_Flag& flag)
{
	switch (flag)
	{
	case CRE_DISPLAY_FULLSCREEN:
		SDL_SetWindowFullscreen(CREVWindow, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowPosition(CREVWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		break;

	case CRE_DISPLAY_BORDERLESS_FULLSCREEN:
		SDL_SetWindowFullscreen(CREVWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_SetWindowPosition(CREVWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		break;

	case CRE_DISPLAY_WINDOWED:
		SDL_SetWindowFullscreen(CREVWindow, 0);
		SDL_SetWindowPosition(CREVWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

		//need code here for display mode scale to fit.
		break;

	default:
		break;
	}

	fullscreenFlag = flag;

	setResolution(windowResolutionX, windowResolutionY);
}

void CRE_Video::setScaleMode(const CRE_Scale_Mode& flag)
{
	scaleMode = flag;

	//update window display with scale mode
	setResolution(windowResolutionX, windowResolutionY);
}

void CRE_Video::getViewportRect(SDL_Rect* r)
{
	*r = { cameraPosX, cameraPosY, RENDERING_SCREEN_WIDTH, RENDERING_SCREEN_HEIGHT };
}

#ifdef FRAMERATE_COUNTER
float video::getFrameRate()
{
	return frameRate;
}
#endif