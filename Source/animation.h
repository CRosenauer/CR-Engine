#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_rect.h>
#include <string>

#include "texture.h"

enum CREAnimationFlag
{
	ANIMATION_NOLOOP,
	ANIMATION_LOOP
};

struct animation
{
	const textureData textureData;

	const unsigned int frameCount;
	//number of frames this texture is used.
	//CREngine runs at 60 Hz, use this as a baseline.

	const animation* nextFrame;
	//pointer to the next frame of animation
};

typedef animation* animationPtr;

#endif //ANIMATION_H