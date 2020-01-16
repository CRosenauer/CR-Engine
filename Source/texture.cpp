#include "texture.h"

extern SDL_Renderer* CRERenderer;

texture::texture()
{
	tDest = { 0, 0, 0, 0 };
	tSource = tDest;
	xOffset = 0;
	yOffset = 0;
}

void texture::loadTexture(const textureData& text, const SDL_Rect& dest)
{
	std::string tempString = getFilePath(text.path, GRAPHICS);
	SDL_Surface* tempSurface = IMG_Load(tempString.c_str());

	if (tempSurface == NULL)
	{
		printf("Image of path: %s cannot be loaded. SDL_image Error: %s\n", tempString.c_str(), IMG_GetError());
		exit(-1);
	}
	else
	{
		if (tTexture != NULL)
		{
			SDL_DestroyTexture(tTexture);
		}

		tTexture = SDL_CreateTextureFromSurface(CRERenderer, tempSurface);

		if (tTexture == NULL)
		{
			printf("Texture of path: %s cannot be created.\nError: %s", tempString.c_str(), SDL_GetError());
			exit(-1);
		}
	}

	SDL_FreeSurface(tempSurface);

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