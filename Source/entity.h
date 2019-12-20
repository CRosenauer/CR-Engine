#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>

#include "texture.h"

using namespace std;

class entity
{
public:
	entity();

	//sets texture data based on passed data
	//loads texture of .png image of path
	//loads source to draw from source
	//loads location to draw to from dest
	void setTexture(const std::string& path, SDL_Rect source, SDL_Rect dest, const int& xOffset, const int& yOffset);

	void setTextureDest(SDL_Rect* dest);

	//sets eTexture to passed texture.
	void setTexture(const texture& text);

	//returns the texture associated with the entity
	texture* getTexture();

	//sets posX to x, posY to y, posZ to z
	void setPosition(int x, int y, int z);
	
	//returns position array {posX, posY, posZ}
	void getPosition(int pos[3]);
	
	//virtual function for entity logic
	//child classes created for individual entities (player char, npcs, etc)
	void entityLogic();

private:
	//horizontal, vertical, and depth position of the entity respectively.
	//by default texture is centered on the xyz position on the entity.
	//this can be overwritten with setTexture()
	int posX, posY, posZ;

	texture eTexture;

	bool rectIsUndefined(SDL_Rect);

	//animation eAnimation;

	//Entity is a combination of logic and texture data
	//Entities internal logic handles
};

#endif //ENTITY_H