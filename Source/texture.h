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

//Flips for flipping sprites
//Set flips the flag
//Reset removes flip
//Toggle inverts flip
//UD flips the texture up-down
//LR flips the texture left-right
enum CRE_FlipFlag
{
	CRE_SetFlipUD,
	CRE_ResetFlipUD,
	CRE_ToggleFlipUD,
	CRE_SetFlipLR,
	CRE_ResetFlipLR,
	CRE_ToggleFlipLR,
	CRE_ResetFlip
};

std::string renderingFlagToString(const CRE_RenderingFlag& flag);

struct CRE_TextureData
{
	std::string path;	//file name of the image to load ex.) "image.png"
	SDL_Rect source;	//rectangle in the image which the video system will use to draw from
	int xOffset;		//offsets to have the 0 point of the texture not on the origin of the entity.
	int yOffset;

	Uint8 alpha;		//transparency of the texture. 0 is completely transparent, 255 is completely opaque.
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

	void loadTexture(const CRE_TextureData& text);

	SDL_Texture* getTexture();

	SDL_Rect getSourceRect();

	SDL_Rect getDestRect();

	void setRect(SDL_Rect source, SDL_Rect dest);

	void setRenderingFlag(const CRE_RenderingFlag& flag) { renderingFlag = flag; }

	CRE_RenderingFlag getRenderingFlag() { return renderingFlag; }

	float getXScale() { return xScale; }
	float getYScale() { return yScale; }
	
	double getRotationDegree() { return rotationAngle; }
	SDL_RendererFlip getFlipFlag() { return flipFlag; }

	void  setAlpha(const Uint8& a);
	Uint8 getAlpha();

	void setXScale(const float& xS) { xScale = abs(xS); }
	void setYScale(const float& yS) { yScale = abs(yS); }
	
	void setRotationDegree(const double& angle) { rotationAngle = angle; }
	void addRotationDegree(const double& angle) { rotationAngle += angle; }

	void setFlipFlag(const CRE_FlipFlag& flag);

	//flip[0]: Up-down flip active.
	//flip[1]: Left-right flip active.
	void getFlipFlag(bool flip[2]);

	int getXOffset() { return xOffset; }
	int getYOffset() { return yOffset; }

private:
	SDL_Texture* tTexture = NULL;
	SDL_Rect     tSource;
	SDL_Rect     tDest;

	//used for overloaded = operator and copy constructor.
	CRE_TextureData textData;

	//offsets used to create textures that aren't zeroed on the entity position
	int xOffset, yOffset;

	//scales used for texture stretching
	float xScale, yScale;

	//position to hold which point to rotate around for texture rotation
	int rotationCenterX, rotationCenterY;

	//degree to hold rotation angle of the texture. Angle is clockwise.
	double rotationAngle;

	//flag for which way to flip the texture (if the texture is flipped)
	//only used internally for communicating with SDL. For CRE Flip flags see enum
	//CRE_FlipFlag
	SDL_RendererFlip flipFlag;

	CRE_RenderingFlag renderingFlag;

	//measurement of texture alpha (transparency). 255 is completely opaque, 0 is completely transparent.
	Uint8 alpha;
};

#endif //TEXTURE_H