#ifndef FOREBACKGROUNDHANDLER_H
#define FOREBACKGROUNDHANDLER_H

#include <vector>

#include "texture.h"
#include "animation.h"
#include "renderingFlags.hpp"

using namespace std;

/*
	ground.h

	header for everything related to foregrounds and background
	note that ground information is intended to be stored as const
	structs rather than through dynamic memory.
*/



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
	const textureData text;		//information for texture data
	const animation animation;	//information for animation data

	~groundImageData() {}
};

//struct to contain foreground and background data
struct groundData
{
	const IMAGE_TYPE imageType;		//flag for if the ground is animated or a static texture
	const groundImageData data;		//union containing texture and animation data
	const ANIMATION_FLAG animFlag;	//flag if the animation is looping or not
	const RENDERING_FLAG flag;		//flag for the rendering layer this 
	const int groundDepth;			//data containing the depth of the ground layer.
									//Larger depth means higher priority (currently unused)

	const groundData* next;			//pointer to the next ground layer

	~groundData() {}
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
		
	int posX, posY, posZ;
};

//resets current background and foreground vetors and loads passed groundData
void setGround(const groundData& groundDat);

//loads passed groundData without resetting all foreground and background vectors.
void loadGround(const groundData& groundDat);

//removes all foreground and background layers of the passed rendering flag
void resetGround(const RENDERING_FLAG& flag);

//removes all loaded foreground and background layers
void resetGround();

//iterates through both the foreground and background vectors and
//updates each layer of the grounds' animation (if applicible)
void updateGrounds();

//returns true if both the foreground and backgrounds vectors are empty
//returns false in all other cases
bool groundsEmpty();

#endif //FOREBACKGROUNDHANDLER_H