#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_rect.h>
#include <string>

enum CREAnimationFlag
{
	ANIMATION_NOLOOP,
	ANIMATION_LOOP
};

struct animation
{
	const std::string path;
	//the path of the image being used in this frame of animation

	const SDL_Rect source;
	//a SDL_Rect of which part of the image should be used.

	const int xOffset;
	const int yOffset;
	//integer values representing the vector which is the offset
	//from the center of the object to the rendering corner of the
	//sprite.
	//

	const unsigned int frameCount;
	//number of frames this texture is used.
	//CREngine runs at 60 Hz, use this as a baseline.

	const animation* nextFrame;
	//pointer to the next frame of animation
};

typedef animation* animationPtr;

#endif //ANIMATION_H