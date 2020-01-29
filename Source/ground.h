#ifndef FOREBACKGROUNDHANDLER_H
#define FOREBACKGROUNDHANDLER_H

#include <vector>

#include "entity.h"

/*
	Renderings flags for quick reference
enum RENDERINGFLAG
{
	RENDERINGFLAG_SPRITE,
	RENDERINGFLAG_BACKGROUND,
	RENDERINGFLAG_FOREGROUND,
	RENDERINGFLAG_STATIC_BACKGROUND,
	RENDERINGFLAG_STATIC_FOREGROUND
};
*/

enum IMAGE_TYPE
{
	TEXTURE,	//0
	ANIMATION	//1
};

//union to contain texture data used in the ground struct
//text contains a static texture
//texture* contains a pointer to an already in use texture
//for use or say item incons on the HUD
//animation contains a animation
union groundImageData
{
	textureData text;
	animation animation;
};

//struct to contain foreground and background data
struct groundData
{
	const IMAGE_TYPE imageType;
	const groundImageData data;
	ANIMATION_FLAG animFlag;
	const RENDERING_FLAG flag;
	const int groundDepth;
	const groundData* next;
};

//class used as container for foreground and background data
class ground
{
public:
	ground();
	ground(const groundData& data);

	//mutators
	void loadGround(const groundData& groundDat);

	//accessors
	RENDERING_FLAG getRenderingFlag() { return renderingFlag; }
	texture* getTexture() { return &gTexture; }

	//functions to update texture data for animations
	//to be used at the end of a frame render.
	//don't touch it, just let the engine handle this function.
	void update();

private:
	//internal functions for setting image data.
	void setRenderingFlag(const RENDERING_FLAG& flag) { renderingFlag = flag; }
	void setTexture(const texture& text) { gTexture = text; }
	void setAnination(const animation& anim, const ANIMATION_FLAG& flag) { gAnimation = &anim; gFirstAnim = &anim; }

	texture   gTexture;
	const animation* gAnimation;
	const animation* gFirstAnim;
	int animFrameCount;

	SDL_Rect destRect = { 0, 0, 0, 0 };

	IMAGE_TYPE imageType;

	RENDERING_FLAG renderingFlag;
		
	int posX, posY;
};

void setGround(const groundData& groundDat);

void resetGround(RENDERING_FLAG flag);

void updateGrounds();

#endif //FOREBACKGROUNDHANDLER_H