#include "texture.h"

extern SDL_Renderer* CRERenderer;

texture::texture()
{
	tDest = { 0, 0, 0, 0 };
	tSource = tDest;
	xOffset = 0;
	yOffset = 0;
}

texture::~texture()
{
	SDL_DestroyTexture(tTexture);
}

texture::texture(const texture& t)
{
	//loads internal variables
	tDest    = t.tDest;
	tSource  = t.tSource;
	xOffset  = t.xOffset;
	yOffset  = t.yOffset;
	textData = t.textData;

	//creates a new SDL_Texture for internal texture rendering
	loadTexture(textData, tDest);
}
void texture::operator = (const texture& t)
{
	//deallocate old texture
	SDL_DestroyTexture(tTexture);

	//loads internal variables
	tDest = t.tDest;
	tSource = t.tSource;
	xOffset = t.xOffset;
	yOffset = t.yOffset;
	textData = t.textData;

	//creates a new SDL_Texture for internal texture rendering
	loadTexture(textData, tDest);
}

void texture::loadTexture(const textureData& text, const SDL_Rect& dest)
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

SDL_Texture* texture::getTexture()
{
	return tTexture;
}

SDL_Rect texture::getSourceRect()
{
	return tSource;
}

SDL_Rect texture::getDestRect()
{
	return tDest;
}

void texture::setRect(SDL_Rect source, SDL_Rect dest)
{
	tSource = source;
	tDest   = dest;
}