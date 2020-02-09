#ifndef TESTGROUNDS_H
#define TESTGROUNDS_H

#include "texture.h"
#include "animation.h"
#include "ground.h"

/*
struct textureData
{
	std::string path;
	SDL_Rect source;
	int xOffset;
	int yOffset;
};

struct animation
{
	const textureData* textureData;

	const unsigned int frameCount;
	//number of frames this texture is used.
	//CREngine runs at 60 Hz, use this as a baseline.

	const animation* nextFrame;
	//pointer to the next frame of animation
};

union groundImageData
{
	const textureData* text;		//information for texture data
	const animation* anim;	//information for animation data

	//constructors for initialization
	groundImageData(const textureData& t) : text(t) {}
	groundImageData(const animation& a) : anim(a) {}

	~groundImageData() {}		//unused destructor. Included to prevent compilation warnings
};


struct groundData
{
	const IMAGE_TYPE imageType;		//flag for if the ground is animated or a static texture
	const groundImageData data;		//union containing texture and animation data
	const ANIMATION_FLAG animFlag;	//flag if the animation is looping or not
	const RENDERING_FLAG flag;		//flag for the rendering layer this
	const unsigned int groundDepth;	//data containing the depth of the ground layer.
									//Larger depth means higher priority (currently unused)

	const groundData* next;			//pointer to the next ground layer

	~groundData() {}				//unused destructor. Included to revent compilations warnings
};
*/

const textureData test_background_anim_data_00 =
{
	"test_background_anim_00.png",
	{0, 0, 640, 480},
	0,
	0
};

const textureData test_background_anim_data_01 =
{
	"test_background_anim_01.png",
	{0, 0, 640, 480},
	0,
	0
};

const textureData test_HUD_data =
{
	"test_HUD.png",
	{0, 0, 640, 480},
	0,
	0
};

const textureData test_scrolling_foreground_data =
{
	"test_scrolling_foreground.png",
	{0, 0, 1280, 960},
	0,
	0
};

const animation test_background_anim_01 =
{
	&test_background_anim_data_01,
	15,
	NULL
};

const animation test_background_anim_00 =
{
	&test_background_anim_data_00,
	15,
	&test_background_anim_00
};

const union groundImageData test_background_anim = &test_background_anim_00;

const union groundImageData test_HUD = &test_HUD_data;

const union groundImageData test_scrolling_foreground = &test_scrolling_foreground_data;

const groundData test_ground_02 =
{
	TEXTURE,
	&test_scrolling_foreground,
	ANIMATION_NOLOOP,
	RENDERINGFLAG_FOREGROUND,
	0,
	NULL
};

const groundData test_ground_01 =
{
	TEXTURE,
	&test_HUD,
	ANIMATION_NOLOOP,
	RENDERINGFLAG_STATIC_FOREGROUND,
	0,
	&test_ground_02
};

const groundData test_ground =
{
	ANIMATION,
	&test_background_anim,
	ANIMATION_LOOP,
	RENDERINGFLAG_STATIC_BACKGROUND,
	0,
	&test_ground_01
};

#endif //TESTGROUND_H