#ifndef FOREBACKGROUNDHANDLER_H
#define FOREBACKGROUNDHANDLER_H

#include <SDL_rect.h>

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


enum CRE_GroundImageType
{
	TEXTURE,	//0
	ANIMATION	//1
};

//union to contain texture data used in the ground struct
//text contains a static texture
//texture* contains a pointer to an already in use texture
//for use or say item incons on the HUD
//animation contains a animation
union CRE_GroundImageData
{
	const CRE_TextureData* text;	//information for texture data
	const CRE_Animation* anim;		//information for animation data

	~CRE_GroundImageData() {}		//unused destructor. Included to prevent compilation warnings
};

//struct to contain foreground and background data
struct CRE_GroundData
{
	const CRE_GroundImageType imageType;		//flag for if the ground is animated or a static texture
	const CRE_GroundImageData* data;		//union containing texture and animation data
	const CRE_AnimationFlag animFlag;	//flag if the animation is looping or not
	const CRE_RenderingFlag flag;		//flag for the rendering layer this 
	const unsigned int groundDepth;	//data containing the depth of the ground layer.
									//Larger depth means higher priority (currently unused)

	const CRE_GroundData* next;			//pointer to the next ground layer

	~CRE_GroundData() {}				//unused destructor. Included to revent compilations warnings
};

//class used as container for foreground and background data
class CRE_Ground
{
public:
	CRE_Ground();
	CRE_Ground(const CRE_GroundData& data);

	~CRE_Ground();

	//loads passed ground data to this current ground
	void loadGround(const CRE_GroundData& groundDat);

	//accessors
	CRE_RenderingFlag getRenderingFlag() { return renderingFlag; }
	CRE_Texture* getTexture() { return &gTexture; }
	void getPosition(int pos[3]) { pos[0] = posX; pos[1] = posY; pos[2] = posZ; }
	void setPosition(int pos[3]) { posX = pos[0]; posY = pos[2]; posZ = pos[3]; }

	void  setAlpha(const Uint32 a) { gTexture.setAlpha(a); }
	Uint8 getAlpha() { return gTexture.getAlpha(); }

	void setScale(const float& x, const float& y);
	void getScale(float scale[2]);

	unsigned int getDepth() { return posZ; }

	//functions to update texture data for animations
	//to be used at the end of a frame render.
	//don't touch it, just let the engine handle this function.
	void updateAnimation();

private:
	//internal functions for setting image data.
	void setRenderingFlag(const CRE_RenderingFlag& flag) { renderingFlag = flag; }
	void setTexture(const CRE_Texture& text) { gTexture = text; }
	void setAnination(const CRE_Animation& anim, const CRE_AnimationFlag& flag) { gAnimation = &anim; gFirstAnim = &anim; }

	//member image information
	CRE_Texture   gTexture;
	const CRE_Animation* gAnimation;
	const CRE_Animation* gFirstAnim;
	int animFrameCount;

	SDL_Rect destRect = { 0, 0, 0, 0 };

	CRE_GroundImageType imageType;

	CRE_RenderingFlag renderingFlag;
		
	int posX, posY;
	unsigned int posZ;
};

//resets current background and foreground vetors and loads passed groundData
void setGround(const CRE_GroundData& groundDat);

//loads passed groundData without resetting all foreground and background vectors.
void loadGround(const CRE_GroundData& groundDat);

//removes all foreground and background layers of the passed rendering flag
void resetGround(const CRE_RenderingFlag& flag);

//removes all loaded foreground and background layers
void resetGround();

//iterates through both the foreground and background vectors and
//updates each layer of the grounds' animation (if applicible)
void updateGrounds();

//returns true if both the foreground and backgrounds vectors are empty
//returns false in all other cases
bool groundsEmpty();

#endif //FOREBACKGROUNDHANDLER_H