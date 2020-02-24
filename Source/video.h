#ifndef VIDEO_H
#define VIDEO_H

#define FRAMECAP_60
#define FRAMERATE_COUNTER

#include <SDL.h>
#include <SDL_Surface.h>
#include <SDL_Render.h>
#include <queue>
#include <vector>
#include <string>

#include "entity.h"
#include "texture.h"
#include "timer.h"
#include "renderingFlags.hpp"
#include "ground.h"

/* video.h, main class used to write images to the screen
 * 
 * general idea is that a texture is loaded from entity to some data member of video.h
 * then this process is completed until frame is done rendering
 * finally, frame is loaded to window.
*/

using namespace std;

class video
{
public:
	//Constructor Block
	video();
	video(const std::string& TITLE, const int& SCREENWIDTH, const int& SCREENHEIGHT, const Uint32& WINDOWFLAG);
	//initialized the rendering window and sets all over internal variables to NULL

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
	void loadTexture(texture* texture, RENDERING_FLAG flag);

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

	//returns current game resolution
	//pos[0] = width, pos[1] = height
	void getResolution(int pos[2]);

#ifdef FRAMERATE_COUNTER
	float getFrameRate();
#endif

private:
	std::string title;

	int screenWidth, screenHeight;

	//positions for the view port's top left corner
	int cameraPosX, cameraPosY;

	Uint32 windowFlag;

	SDL_Window*   CREVWindow;
	SDL_Surface*  CREVSurface;


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
	queue<texture*> spriteQueue;
	queue<texture*> backgroundQueue;
	queue<texture*> foregroundQueue;
	queue<texture*> staticBackgroundQueue;
	queue<texture*> staticForegroundQueue;
};

#endif //VIDEO_H