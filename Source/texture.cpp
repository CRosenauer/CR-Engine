#include "texture.h"

extern SDL_Renderer* CRERenderer;

texture::texture()
{

}

texture::texture(const std::string& path, SDL_Rect source, SDL_Rect dest)
{
	std::string tempString = getFilePath(path, GRAPHICS);
	loadTexture(tempString.c_str(), source, dest);
	tSource = source;
	tDest   = dest;
}

void texture::loadTexture(const std::string& path, SDL_Rect source, SDL_Rect dest)
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
		tTexture = SDL_CreateTextureFromSurface(CRERenderer, tempSurface);

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

void texture::autoSetRect()
{
	tSource = {};
	tDest   = {};
}

void texture::setRect(SDL_Rect source, SDL_Rect dest)
{
	tSource = source;
	tDest   = dest;
}