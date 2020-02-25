#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#include "file.h"


enum CRE_RotationFlag
{
	ENTITY_CENTER,			//rotation point as the center point of the entity which owns this texture
	TEXTURE_ZERO_CORNER,	//rotation point as the top-left corner of the texture
	CUSTOM					//rotation point set relative to the entity which owns this texture
};

struct CRE_TextureData
{
	std::string path;
	SDL_Rect source;
	int xOffset;
	int yOffset;
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
};

#endif //TEXTURE_H