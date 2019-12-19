#ifndef VIDEO_H
#define VIDEO_H

#include <SDL.h>
#include <SDL_Surface.h>
#include <SDL_Render.h>
#include <queue>
#include <string>

#include "texture.h"


enum CREVRenderingFlag
{
	CRE_V_TEXTURE_SPRITE,
	CRE_V_TEXTURE_BACKGROUND,
	CRE_V_TEXTURE_FOREGROUND
};

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
	video(const std::string& TITLE, const int& SCREENWIDTH, const int& SCREENHEIGHT, const Uint32& WINDOWFLAG, SDL_Renderer*& renderer);
	//initialized the rendering window and sets all over internal variables to NULL

	//Graphics Queue Loading
	void loadTexture(texture* texture, CREVRenderingFlag flag);
	//loads an entity, background, or foreground to rendering queues
	//for drawing to screen
	//drawing is handled by void render()

	//Render current frame
	void render();
	//renders current game screen
	//clears frame and then renders every queued entity
	//then renders to game window

	void init();
	//initializes video rendering stuctures
	//called once at the beginning of the game in void CREInit();

private:
	std::string title;
	int screenWidth, screenHeight;
	Uint32 windowFlag;

	SDL_Window*   CREVWindow;
	SDL_Surface*  CREVSurface;
	SDL_Renderer* CREVRenderer;

	queue<texture*> spriteQueue;
	queue<texture*> backgroundQueue;
	queue<texture*> foregroundQueue;
	//temperary queues for loading sprites, etc.
	//is orderly loaded to textureQueue before rendering
	//this way memory fragmentation shouldnt be a huge issue.
	//queues add potential memory fragmentation problems
	//for future iterations, make vectors with loadsize from file
	//or have a set vram size in file and manage loading of backgrounds, sprites, and foregrounds
};

#endif //VIDEO_H