#include "texture.h"

extern SDL_Renderer* CRERenderer;

std::string renderingFlagToString(const CRE_RenderingFlag& flag)
{
	std::string s;

	switch (flag)
	{
	case RENDERINGFLAG_BACKGROUND:
		s = "RENDERINGFLAG_BACKGROUND";
		break;
	case RENDERINGFLAG_STATIC_BACKGROUND:
		s = "RENDERINGFLAG_STATIC_BACKGROUND";
		break;
	case RENDERINGFLAG_SPRITE:
		s = "RENDERINGFLAG_SPRITE";
		break;
	case RENDERINGFLAG_STATIC_FOREGROUND:
		s = "RENDERINGFLAG_STATIC_FOREGROUND";
		break;
	case RENDERINGFLAG_FOREGROUND:
		s = "RENDERINGFLAG_FOREGROUND";
		break;
	default:
		s = "";
		break;
	}

	return s;
}

CRE_Texture::CRE_Texture()
{
	tDest = { 0, 0, 0, 0 };
	tSource = tDest;
	xOffset = 0;
	yOffset = 0;
	xScale = 1;
	yScale = 1;
	rotationCenterX = 0;
	rotationCenterY = 0;
	rotationAngle = 0.0;
	flipFlag = SDL_FLIP_NONE;
	rotationFlag = ENTITY_CENTER;
	alpha = 255;
	renderingFlag = RENDERINGFLAG_SPRITE;
}

CRE_Texture::~CRE_Texture()
{
	SDL_DestroyTexture(tTexture);
}

CRE_Texture::CRE_Texture(const CRE_Texture& t)
{
	//loads internal variables
	tDest    = t.tDest;
	tSource  = t.tSource;
	xOffset  = t.xOffset;
	yOffset  = t.yOffset;
	textData = t.textData;

	xScale = t.xScale;
	yScale = t.yScale;
	rotationCenterX = t.rotationCenterX;
	rotationCenterY = t.rotationCenterY;
	rotationAngle = t.rotationAngle;
	flipFlag = t.flipFlag;
	rotationFlag = t.rotationFlag;
	alpha = t.alpha;

	renderingFlag = t.renderingFlag;

	//creates a new SDL_Texture for internal texture rendering
	loadTexture(textData, tDest);
}
void CRE_Texture::operator = (const CRE_Texture& t)
{
	//deallocate old texture
	SDL_DestroyTexture(tTexture);

	//loads internal variables
	tDest = t.tDest;
	tSource = t.tSource;
	xOffset = t.xOffset;
	yOffset = t.yOffset;
	textData = t.textData;

	xScale = t.xScale;
	yScale = t.yScale;
	rotationCenterX = t.rotationCenterX;
	rotationCenterY = t.rotationCenterY;
	rotationAngle = t.rotationAngle;
	flipFlag = t.flipFlag;
	rotationFlag = t.rotationFlag;

	renderingFlag = t.renderingFlag;

	//creates a new SDL_Texture for internal texture rendering
	loadTexture(textData, tDest);
}

void CRE_Texture::loadTexture(const CRE_TextureData& text, const SDL_Rect& dest)
{
	textData = text;

	std::string tempString = getFilePath(text.path, GRAPHICS);
	SDL_Surface* tempSurface = IMG_Load(tempString.c_str());

	if (tempSurface == NULL)
	{
		printf("Image of path: %s cannot be loaded. SDL_image Error: %s\n", tempString.c_str(), IMG_GetError());
	}
	else
	{
		if (tTexture != NULL)
		{
			SDL_DestroyTexture(tTexture);
			tTexture = NULL;
		}

		tTexture = SDL_CreateTextureFromSurface(CRERenderer, tempSurface);

		if (tTexture == NULL)
		{
			printf("Texture of path: %s cannot be created.\nError: %s", tempString.c_str(), SDL_GetError());
			//exit(-1);
		}
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
	
	tSource = text.source;
	tDest = dest;

	tDest.x -= xOffset;
	tDest.y -= yOffset;
}

SDL_Texture* CRE_Texture::getTexture()
{
	return tTexture;
}

SDL_Rect CRE_Texture::getSourceRect()
{
	return tSource;
}

SDL_Rect CRE_Texture::getDestRect()
{
	return tDest;
}

void CRE_Texture::setRect(SDL_Rect source, SDL_Rect dest)
{
	tSource = source;
	tDest   = dest;
}

SDL_Point CRE_Texture::getRotationCenter()
{
	SDL_Point rotationCenter;
	switch (rotationFlag)
	{
	default:
	case ENTITY_CENTER:
		rotationCenter.x = tDest.x + xOffset;
		rotationCenter.y = tDest.y + yOffset;
		break;

	case TEXTURE_CENTER:
		rotationCenter.x = tDest.x;
		rotationCenter.y = tDest.y;
		break;

	case CUSTOM:
		rotationCenter.x = rotationCenterX;
		rotationCenter.y = rotationCenterY;
		break;
	}

	return rotationCenter;
}

void CRE_Texture::getRotationCenter(int center[2])
{
	//switch for cases depending on rotation center mode.
	switch (rotationFlag)
	{
	default:
	case ENTITY_CENTER:
		center[0] = tDest.x + xOffset;
		center[1] = tDest.y + yOffset;
		break;

	case TEXTURE_CENTER:
		center[0] = tDest.x;
		center[1] = tDest.y;
		break;

	case CUSTOM:
		center[0] = rotationCenterX;
		center[1] = rotationCenterY;
		break;
	}
}

void CRE_Texture::setRotationCenter(const int& x, const int& y)
{
	rotationFlag = CUSTOM;

	rotationCenterX = x;
	rotationCenterY = y;
}