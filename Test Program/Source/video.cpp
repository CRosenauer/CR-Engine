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
		//exit(-1);
	}

	//associates gSurface with the rendering window
	CREVSurface = SDL_GetWindowSurface(CREVWindow);
	if (CREVSurface == NULL)
	{
		printf("Video surface cannot be loaded to assigned from window.\nError: %s", SDL_GetError());
		//exit(-1);
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
	
	//render frame to screen.
	SDL_RenderPresent(CREInternalRenderer);

#ifdef FRAMECAP
	pollFrameTimer();
	setFrameTimer();
#endif

#ifdef FRAMERATE_COUNTER
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();

	frameRate = 1000.0 / ( (float) currentTicks - (float) prevTicks ) ;
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
float CRE_Video::getFrameRate()
{
	return frameRate;
}
#endif

void CRE_Video::setFrameCap(const int& frameCap)
{
	setFrameRate(frameCap);
}