#include "texture.h"

texture::texture()
{
	tRenderer = NULL;
	tTexture  = NULL;
	tSource   = NULL;
	tDest     = NULL;
}

texture::texture(const std::string& path, SDL_Rect* source, SDL_Rect* dest, SDL_Renderer* renderer)
{
	std::string tempString = getFilePath(path, GRAPHICS);
	loadTexture(tempString.c_str(), source, dest);
	tSource = source;
	tDest   = dest;
	tRenderer = renderer;
}

void texture::loadTexture(const std::string& path, SDL_Rect* source, SDL_Rect* dest)
{
	std::string tempString = getFilePath(path, GRAPHICS);
	SDL_Surface* tempSurface = IMG_Load(tempString.c_str());
	if (tempSurface == NULL)
	{
		printf("Image of path: %s cannot be loaded. SDL_image Error: %s\n", tempString.c_str(), IMG_GetError());
		exit(-1);
	}
	else
	{
		tTexture = SDL_CreateTextureFromSurface(tRenderer, tempSurface);

		if (tTexture == NULL)
		{
			printf("Texture of path: %s cannot be created.\nError: %s", tempString.c_str(), SDL_GetError());
			exit(-1);
		}

		SDL_FreeSurface(tempSurface);
	}

	tSource = source;
	tDest   = dest;
}

void texture::setRenderer(SDL_Renderer* renderer)
{
	tRenderer = renderer;
}

SDL_Texture* texture::getTexture()
{
	return tTexture;
}

SDL_Rect* texture::getSourceRect()
{
	return tSource;
}

SDL_Rect* texture::getDestRect()
{
	return tDest;
}

void texture::autoSetRect()
{
	tSource = NULL;
	tDest   = NULL;
}

void texture::setRect(SDL_Rect* source, SDL_Rect* dest)
{
	tSource = source;
	tDest   = dest;
}