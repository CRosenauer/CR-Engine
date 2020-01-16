#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#include "file.h"

struct textureData
{
	std::string path;
	SDL_Rect source;
	int xOffset;
	int yOffset;
};

class texture
{
public:
	texture();

	void loadTexture(const textureData& text, const SDL_Rect& dest);

	SDL_Texture* getTexture();

	SDL_Rect getSourceRect();

	SDL_Rect getDestRect();

	void setRect(SDL_Rect source, SDL_Rect dest);

private:
	SDL_Texture* tTexture = NULL;
	SDL_Rect     tSource;
	SDL_Rect     tDest;

	int xOffset, yOffset;
};

#endif //TEXTURE_H