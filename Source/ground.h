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
	TEXTURE_PTR,//1
	ANIMATION	//2
};

//union to contain texture data used in the ground struct
//text contains a static texture
//texture* contains a pointer to an already in use texture
//for use or say item incons on the HUD
//animation contains a animation
union groundImageData
{
	texture text;
	texture* texturePtr;
	animation animation;
};

//struct to contain foreground and background data
struct groundData
{
	IMAGE_TYPE imageType;
	groundImageData data;
	RENDERINGFLAG flag;
	ground* next;
};

//class used as container for foreground and background data
class ground
{
public:
	ground();
	ground(const groundData& data);

	//mutators
	void setRenderingFlag(const RENDERINGFLAG& flag) { renderingFlag = flag; }
	void setTexture(const texture& text) { gTexture = text; }
	void setAnination(const animation& anim, const ANIMATION_FLAG& flag) { gAnimation = &anim; gFirstAnim = &anim; }
	void setRenderingFlag(const RENDERINGFLAG& flag) { renderingFlag = flag; }

	//accessors
	RENDERINGFLAG getRenderingFlag() { return renderingFlag; }

	void update();

	void updateAnim();

private:
	texture   gTexture;
	const animation* gAnimation;
	const animation* gFirstAnim;

	IMAGE_TYPE imageType;

	RENDERINGFLAG renderingFlag;
};

void setGround(const groundData& groundDat);

void resetGround(RENDERINGFLAG flag);

void updateGrounds();

#endif //FOREBACKGROUNDHANDLER_H