#include "texture.h"

extern SDL_Renderer* CREInternalRenderer;

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

	renderingFlag = t.renderingFlag;

	//creates a new SDL_Texture for internal texture rendering
	loadTexture(textData, tDest);
}

void CRE_Texture::loadTexture(const CRE_TextureData& text, const SDL_Rect& dest)
{
	//set and shuffle internal texture-dependant variables
	textData = text;

	tSource = text.source;
	tDest = dest;

	xOffset = text.xOffset;
	yOffset = text.yOffset;

	tDest.x -= xOffset;
	tDest.y -= yOffset;

	//load texture into memory
	std::string tempString = getFilePath(text.path, GRAPHICS);
	SDL_Surface* tempSurface = IMG_Load(tempString.c_str());

	if (tempSurface == NULL)
	{
		//printf("Image of path: %s cannot be loaded. SDL_image Error: %s\n", tempString.c_str(), IMG_GetError());
	}
	else
	{
		if (tTexture != NULL)
		{
			SDL_DestroyTexture(tTexture);
			tTexture = NULL;
		}

		tTexture = SDL_CreateTextureFromSurface(CREInternalRenderer, tempSurface);

		if (tTexture == NULL)
		{
			//printf("Texture of path: %s cannot be created.\nError: %s", tempString.c_str(), SDL_GetError());
		}

		if (SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_BLEND) != 0)
		{
			//printf("Texture blend mode not set.\nSDL Error: %s\n", SDL_GetError());
		}
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
}

void CRE_Texture::loadTexture(const CRE_TextureData& text)
{
	//set and shuffle internal texture-dependant variables
	textData = text;
	SDL_Rect dest = tDest;

	tDest.x += xOffset;
	tDest.y += yOffset;

	xOffset = text.xOffset;
	yOffset = text.yOffset;

	tDest.x -= xOffset;
	tDest.y -= yOffset;

	tSource = text.source;

	//load texture into memory
	std::string tempString = getFilePath(text.path, GRAPHICS);
	SDL_Surface* tempSurface = IMG_Load(tempString.c_str());

	if (tempSurface == NULL)
	{
		//printf("Image of path: %s cannot be loaded. SDL_image Error: %s\n", tempString.c_str(), IMG_GetError());
	}
	else
	{
		if (tTexture != NULL)
		{
			SDL_DestroyTexture(tTexture);
			tTexture = NULL;
		}

		tTexture = SDL_CreateTextureFromSurface(CREInternalRenderer, tempSurface);

		if (tTexture == NULL)
		{
			//printf("Texture of path: %s cannot be created.\nError: %s", tempString.c_str(), SDL_GetError());
		}

		if (SDL_SetTextureBlendMode(tTexture, SDL_BLENDMODE_BLEND) != 0)
		{
			//printf("Texture blend mode not set.\nSDL Error: %s\n", SDL_GetError());
		}
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
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

void CRE_Texture::setAlpha(const Uint8& a)
{
	alpha = a;
	if (SDL_SetTextureAlphaMod(tTexture, alpha) != 0)
	{
		//printf("Failed to apply alpha to texture.\nSDL Error:%s\n", SDL_GetError());
	}
}

Uint8 CRE_Texture::getAlpha()
{
	return alpha;
}

void CRE_Texture::setFlipFlag(const CRE_FlipFlag& flag)
{
	switch (flag)
	{
	case CRE_SetFlipUD:
		flipFlag = (SDL_RendererFlip) (flipFlag | SDL_FLIP_VERTICAL);
		break;
	case CRE_ResetFlipUD:
		flipFlag = (SDL_RendererFlip) (flipFlag & ~SDL_FLIP_VERTICAL);
		break;
	case CRE_ToggleFlipUD:
		flipFlag = (SDL_RendererFlip) (flipFlag ^ SDL_FLIP_VERTICAL);
		break;
	case CRE_SetFlipLR:
		flipFlag = (SDL_RendererFlip)(flipFlag | SDL_FLIP_HORIZONTAL);
		break;
	case CRE_ResetFlipLR:
		flipFlag = (SDL_RendererFlip)(flipFlag & ~SDL_FLIP_HORIZONTAL);
		break;
	case CRE_ToggleFlipLR:
		flipFlag = (SDL_RendererFlip)(flipFlag ^ SDL_FLIP_HORIZONTAL); 
		break;
	case CRE_ResetFlip:
		flipFlag = SDL_FLIP_NONE;
	default:
		break;
	}
}

void CRE_Texture::getFlipFlag(bool flip[2])
{
	flip[0] = (flipFlag & SDL_FLIP_VERTICAL) && SDL_FLIP_VERTICAL;
	flip[1] = (flipFlag & SDL_FLIP_HORIZONTAL) && SDL_FLIP_HORIZONTAL;
}

void CRE_Texture::setPosition(const int& x, const int& y)
{
	tDest.x = x - xOffset;
	tDest.y = y - yOffset;
}