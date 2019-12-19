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

	entity(SDL_Renderer*& rend);
	//creater that associates entity with renderer
	//Note: no alternative renderer mutator function exists as renderer is only intended to be set once at the beginning of game

	void setTexture(const std::string& path, SDL_Rect* source, SDL_Rect* dest);
	//sets texture data based on passed data
	//loads texture of .png image of path
	//loads source to draw from source
	//loads location to draw to from dest

	void setTextureDest(SDL_Rect* dest);

	void setTexture(const texture& text);
	//sets eTexture to passed texture.

	texture getTexture();
	//returns the texture associated with the entity

	void setPosition(int x, int y, int z);
	//sets posX to x, posY to y, posZ to z

	void getPosition(int pos[3]);
	//returns position array {posX, posY, posZ}

	void entityLogic();
	//virtual function for entity logic
	//child classes created for individual entities (player char, npcs, etc)

private:
	int posX, posY, posZ;
	//horizontal, vertical, and depth position of the entity respectively.
	//by default texture is centered on the xyz position on the entity.
	//this can be overwritten with setTexture()

	SDL_Renderer* renderer;

	texture eTexture;

	//animation eAnimation;

	//Entity is a combination of logic and texture data
	//Entities internal logic handles 

};

#endif //ENTITY_H