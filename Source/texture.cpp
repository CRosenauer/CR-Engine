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
		//exit(-1);
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