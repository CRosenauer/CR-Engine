#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>

#include "file.h"

class texture
{
public:
	texture();

	texture(const std::string& path, SDL_Rect source, SDL_Rect dest, const int& xOffset, const int& yOffset);

	void loadTexture(const std::string& path, SDL_Rect source, SDL_Rect dest, const int& xOffset, const int& yOffset);

	SDL_Texture* getTexture();

	SDL_Rect getSourceRect();

	SDL_Rect getDestRect();

	void autoSetRect();

	void setRect(SDL_Rect source, SDL_Rect dest);

private:
	SDL_Texture*  tTexture;
	SDL_Rect     tSource;
	SDL_Rect     tDest;

	int xOffset, yOffset;
};

#endif //TEXTURE_H