#ifndef VIDEO_H
#define VIDEO_H

#include <SDL.h>
#include <SDL_Surface.h>
#include <SDL_Render.h>
#include <queue>
#include <vector>
#include <string>

#include "config.h"

#include "entity.h"
#include "texture.h"
#include "timer.h"
#include "ground.h"

/* video.h, main class used to write images to the screen
 * 
 * general idea is that a texture is loaded from entity to some data member of video.h
 * then this process is completed until frame is done rendering
 * finally, frame is loaded to window.
*/

enum CRE_Fullscreen_Flag
{
	CRE_DISPLAY_FULLSCREEN,
	CRE_DISPLAY_BORDERLESS_FULLSCREEN,
	CRE_DISPLAY_WINDOWED
};

enum CRE_Scale_Mode
{
	CRE_STRETCH_TO_FIT,
	CRE_SCALE_TO_FIT
};

using namespace std;

class CRE_Video
{
public:
	//Constructor Block
	CRE_Video();

	//Graphics Queue Loading
	//loads an entity, background, or foreground to rendering queues
	//for drawing to screen
	//drawing is handled by void render()
	//RENDERINGFLAG:
	//RENDERINGFLAG_SPRITE
	//RENDERINGFLAG_BACKGROUND
	//RENDERINGFLAG_FOREGROUND
	//RENDERINGFLAG_STATIC_BACKGROUND
	//RENDERINGFLAG_STATIC_FOREGROUND
	//
	//Flag information can be found in renderingFlags.hpp
	//
	void loadTexture(CRE_Texture* texture, CRE_RenderingFlag flag);

	//Render current frame
	//renders current game screen
	//clears frame and then renders every queued entity
	//then renders to game window
	void render();

	//initializes video rendering stuctures
	//called once at the beginning of the game in void CREInit();
	void init();

	//sets the passed array to the cameraX and cameraY position
	void getCameraPos(int pos[2]);

	//sets the camera position to the values in the passed array.
	//cameraPosX = pos[0], cameraPosY = pos[1]
	void setCameraPos(const int pos[2]);

	//sets the display resolution to the passed values.
	//fails on non-positive values.
	void setResolution(const int& width, const int& height);

	//sets display mode based on the passed flag.
	void setFullscreenMode(const CRE_Fullscreen_Flag& flag);

	//sets video display framecap to the passed integer in frames per second.
	void setFrameCap(const int& frameCap);

	//sets display mode to strech to fit or scale to fit.
	void setScaleMode(const CRE_Scale_Mode& flag);

	void getViewportRect(SDL_Rect* r);

#ifdef FRAMERATE_COUNTER
	float getFrameRate();
#endif

private:
	//positions for the view port's top left corner
	int cameraPosX, cameraPosY;

	Uint32 windowFlag;
	
	SDL_Window*   CREVWindow;
	SDL_Surface*  CREVSurface;
	
	//main renderer for displaying to windows
	SDL_Window* CREDisplayWindow     = NULL;
	SDL_Surface* CREDisplaySurface   = NULL;
	SDL_Renderer* CREDisplayRenderer = NULL;

	CRE_Scale_Mode scaleMode = DEFAULT_SCALE_MODE;
	CRE_Fullscreen_Flag fullscreenFlag = DEFAULT_FULLSCREEN_MODE;


	float windowXScale = (float) DEFAULT_DISPLAY_WIDTH / (float) RENDERING_SCREEN_WIDTH;
	float windowYScale = (float) DEFAULT_DISPLAY_HEIGHT / (float) RENDERING_SCREEN_HEIGHT;
	int windowResolutionX = DEFAULT_DISPLAY_WIDTH;
	int windowResolutionY = DEFAULT_DISPLAY_HEIGHT;

#ifdef FRAMERATE_COUNTER
	float frameRate = 0;
	float prevTicks = 0;
	float currentTicks = 1;
#endif

	//temperary queues for loading sprites, etc.
	//is orderly loaded to textureQueue before rendering
	//this way memory fragmentation shouldnt be a huge issue.
	//queues add potential memory fragmentation problems
	//for future iterations, make vectors with loadsize from file
	//or have a set vram size in file and manage loading of backgrounds, sprites, and foregrounds
	queue<CRE_Texture*> spriteQueue;
	queue<CRE_Texture*> backgroundQueue;
	queue<CRE_Texture*> foregroundQueue;
};

#endif //VIDEO_H