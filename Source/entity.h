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

enum CRE_EntityType
{
	test //0
};

union componentData
{

};

struct CRE_EntityData
{
	CRE_EntityType entityType;
	componentData componentData;
};

class CRE_Entity
{
public:
	CRE_Entity();

	//sets texture data based on passed data
	//loads texture of .png image of path
	//loads source to draw from source
	//loads location to draw to from dest
	void setTexture(const CRE_TextureData& text);

	//sets eTexture to passed texture.
	void setTexture(const CRE_Texture& text);

	//sets rendering flag of the entity. See renderingFlags.hpp for rendering flag information.
	void setRenderingFlag(CRE_RenderingFlag flag);

	//returns the texture associated with the entity
	CRE_Texture* getTexture();

	//kinematic mutators for positon, velocity, and acceleration
	void setPosition(int x, int y, int z);
	void setVelocity(int x, int y, int z);
	void setAcceleration(int x, int y, int z);
	
	//kinematic accessors for position, velocity, and acceleration
	//returns array {x, y, z}
	void getPosition(int pos[3]);
	void getVelocity(int vel[3]);
	void getAcceleration(int acc[3]);
	
	//loads passed animation into memory.
	void setAnimation(const CRE_Animation* anim, const CRE_AnimationFlag& flag);

	//returns ID of the entity
	unsigned int getEntityID();

	//returns the z value of the entity. used to speed up entity texture rendering
	int getDepth();

	//returns current rendering mode of the entity
	CRE_RenderingFlag getRenderingFlag();

	//sets data.entityType to the passed interger.
	void setEntityType(const CRE_EntityType& i);

	//returns current entity type found in data.entityType
	CRE_EntityType getEntityType();

	//returns internal texture's destination rect.
	SDL_Rect getTextureDest();

	//function to update entity's animation frame
	//should be called in update.
	void updateAnimation();

private:
	//kinematic variables of the entity
	//pos, vel, and acc stand for position, velocity, and acceleration respectively.
	//X, Y, Z are the x (E/W), y (N/S), and z (Depth) co-ordinates respectively.
	//variables used in update for position changes.
	int posX, posY, posZ;
	int velX, velY, velZ;
	int accX, accY, accZ;

	CRE_Texture eTexture;

	bool rectIsUndefined(SDL_Rect);

	const CRE_Animation* eAnimation;
	const CRE_Animation* eFirstAnimation;

	int animFrameCount;

	CRE_RenderingFlag renderingFlag;

	unsigned int entityID;

	CRE_EntityData data;
};

#endif //ENTITY_H