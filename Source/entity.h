#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>

#include <cstdio>
#include <vector>

#include "texture.h"
#include "animation.h"
#include "renderingFlags.hpp"

using namespace std;

union componentData
{

};

struct entityData
{
	unsigned int  entityType;
	componentData componentData;
};

class entity
{
public:
	entity();

	//sets texture data based on passed data
	//loads texture of .png image of path
	//loads source to draw from source
	//loads location to draw to from dest
	void setTexture(const textureData& text);

	//sets eTexture to passed texture.
	void setTexture(const texture& text);

	//sets rendering flag of the entity. See renderingFlags.hpp for rendering flag information.
	void setRenderingFlag(RENDERINGFLAG flag);

	//returns the texture associated with the entity
	texture* getTexture();

	//sets posX to x, posY to y, posZ to z
	void setPosition(int x, int y, int z);
	
	//returns position array {posX, posY, posZ}
	void getPosition(int pos[3]);
	
	//loads passed animation into memory.
	void setAnimation(const animation* anim, const CREAnimationFlag& flag);

	//returns ID of the entity
	unsigned int getEntityID();

	//returns the z value of the entity. used to speed up entity texture rendering
	int getDepth();

	//returns current rendering mode of the entity
	RENDERINGFLAG getRenderingFlag();

	//sets data.entityType to the passed interger.
	void setEntityType(const unsigned int& i);

	//returns current entity type found in data.entityType
	unsigned int getEntityType();

	//returns internal texture's destination rect.
	SDL_Rect getTextureDest();

private:
	//horizontal, vertical, and depth position of the entity respectively.
	//by default texture is centered on the xyz position on the entity.
	//this can be overwritten with setTexture()
	int posX, posY, posZ;

	texture eTexture;

	bool rectIsUndefined(SDL_Rect);

	const animation* eAnimation;
	const animation* eFirstAnimation;

	int animFrameCount;

	RENDERINGFLAG renderingFlag;

	unsigned int entityID;

	entityData data;
};


/*** entityBlock accessing functions: ***/

//cycles through entityBlock until entity is found whose ID equals the passed ID
//deallocates said entity from memory and removes the entity* from the vector
void deleteEntity(const unsigned int& entityID);

//pushes a new entity to the entity vector and sets it to defined
//returns the ID of the entity
unsigned int allocateEntity();

//cycles through entityBlock until an entity is found whose internal ID
//matches the passed ID.
//function returns the pointer to said entity.
//if no entity with the passed ID can be found function returns NULL.
entity* entityFromID(const unsigned int& id);


#endif //ENTITY_H