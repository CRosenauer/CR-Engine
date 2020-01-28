#ifndef FOREBACKGROUNDHANDLER_H
#define FOREBACKGROUNDHANDLER_H

#include <vector>

#include "entity.h"

/*
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
	TEXTURE_PTR,
	ANIMATION	//2
};

//union to contain texture data used in the ground struct
//text contains a static texture
//texture* contains a pointer to an already in use texture
//for use or say item incons on the HUD
//animation contains a animation
union groundData
{
	texture text;
	texture* texturePtr;
	animation animation;
};

//struct to contain foreground and background data
struct ground
{
	IMAGE_TYPE imageType;
	groundData data;
	RENDERINGFLAG flag;
	ground* next;
};

void setGround(const ground& ground);

void resetGround(RENDERINGFLAG flag);

void updateGrounds();

#endif //FOREBACKGROUNDHANDLER_H