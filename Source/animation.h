#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_rect.h>
#include <string>

#include "texture.h"

enum CRE_AnimationFlag
{
	ANIMATION_NOLOOP,
	ANIMATION_LOOP
};

struct CRE_Animation
{
	const CRE_TextureData* textureData;

	const unsigned int frameCount;
	//number of frames this texture is used.
	//CREngine runs at 60 Hz, use this as a baseline.

	const CRE_Animation* nextFrame;
	//pointer to the next frame of animation
};

typedef CRE_Animation* CRE_AnimationPtr;

#endif //ANIMATION_H