#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#include "file.h"


enum CRE_RenderingFlag
{
	RENDERINGFLAG_SPRITE,
	RENDERINGFLAG_BACKGROUND,
	RENDERINGFLAG_FOREGROUND,
	RENDERINGFLAG_STATIC_BACKGROUND,
	RENDERINGFLAG_STATIC_FOREGROUND
};

/* Desciprtion of RENDERING_FLAGS members:
 * enum RENDERINGFLAG
 *
 * RENDERINGFLAG_SPRITE
 * Flag to render a texture as a sprite. In the middle priority between
 * background and foreground.
 *
 * RENDERINGFLAG_BACKGROUND
 * Flag to render a texture as a background. The second least priority
 * rendering type behind RENDERINGFLAG_STATIC_BACKGROUND.
 *
 * RENDERINGFLAG_FOREGROUND
 * Flag to render a texture as a foreground. The second highest priority
 * rendering type behind RENDERINGFLAG_STATIC_FOREGROUND.
 *
 * RENDERINGFLAG_STATIC_BACKGROUND
 * Flag to render a background texture that fits the entire screen
 * and does not change position relative to the viewport. Like
 * background  textures, is the least priority rendering type.
 *
 * RENDERINGFLAG_STATIC_FOREGROUND
 * Flag to render a foreground texture that fits the entire screen
 * and does not change position relative to the viewport. Like
 * foregournd textures, is the most priority rendering type.
 *
 *
 * Rendering priority (high to low)
 * RENDERINGFLAG_STATIC_FOREGROUND
 * RENDERINGFLAG_FOREGROUND
 * RENDERINGFLAG_SPRITE
 * RENDERINGFLAG_BACKGROUND
 * RENDERINGFLAG_STATIC_BACKGROUND
 *
*/

std::string renderingFlagToString(const CRE_RenderingFlag& flag);

enum CRE_RotationFlag
{
	ENTITY_CENTER,			//rotation point as the center point of the entity which owns this texture
	TEXTURE_ZERO_CORNER,	//rotation point as the top-left corner of the texture
	CUSTOM					//rotation point set relative to the entity which owns this texture
};

struct CRE_TextureData
{
	std::string path;	//file name of the image to load ex.) "image.png"
	SDL_Rect source;	//rectangle in the image which the video system will use to draw from
	int xOffset;		//offsets to have the 0 point of the texture not on the origin of the entity.
	int yOffset;

	CRE_RenderingFlag flag;
};

class CRE_Texture
{
public:
	//default constructor
	CRE_Texture();

	//copy constructor
	CRE_Texture(const CRE_Texture& t);

	//destructor
	//deallocates internal texture
	~CRE_Texture();

	//overloaded = operatror
	void operator = (const CRE_Texture& t);

	void loadTexture(const CRE_TextureData& text, const SDL_Rect& dest);

	SDL_Texture* getTexture();

	SDL_Rect getSourceRect();

	SDL_Rect getDestRect();

	void setRect(SDL_Rect source, SDL_Rect dest);

	void setRenderingFlag(const CRE_RenderingFlag& flag) { renderingFlag = flag; }

	CRE_RenderingFlag getRenderingFlag() { return renderingFlag; }

private:
	SDL_Texture* tTexture = NULL;
	SDL_Rect     tSource;
	SDL_Rect     tDest;

	//used for overloaded = operator and copy constructor.
	CRE_TextureData textData;

	//offsets used to create textures that aren't zeroed on the entity position
	int xOffset, yOffset;

	//scales used for texture stretching
	unsigned int xScale, yScale;

	//position to hold which point to rotate around for texture rotation
	int rotationCenterX, rotationCenterY;

	//degree to hold rotation angle of the texture.
	double rotationDegree;

	//flag for which way to flip the texture (if the texture is flipped)
	SDL_RendererFlip flipFlag;

	CRE_RotationFlag rotationFlag;

	CRE_RenderingFlag renderingFlag;
};

#endif //TEXTURE_H