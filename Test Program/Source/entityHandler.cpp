#include "entityHandler.h"

#include "config.h"
#include "source/e_Pacman.h"

extern vector<CRE_Entity*> entityBlock;

void swap(vector<CRE_Entity*>& vector, int i, int j)
{
	CRE_Entity* temp = vector[i];
	vector[i] = vector[j];
	vector[j] = temp;
}

void sort(vector<CRE_Entity*>& vector)
{
	int i, j;
	int end = vector.size();

	for (i = 1; i < end; i++)
		for (j = i; j > 0 && (*vector[j - 1]) > (*vector[j]); j--)
			swap(vector, j - 1, j);
}

void deleteEntity(const unsigned int& entityID)
{
	//cycles through entityBus until an entity is found with the passed ID
	//entity with that id is then deallocated from memory and removed from entityBlock.
	for (vector<CRE_Entity*>::iterator itr = entityBlock.begin(); itr < entityBlock.end(); itr++)
	{
		if (entityID == (*itr)->getEntityID())
		{
			delete* itr;

			entityBlock.erase(itr);
			break;
		}
	}
}

void deleteEntityPtr(const CRE_Entity*& e)
{
	//cycles through entityBus until an entity is found with the passed ID
	//entity with that id is then deallocated from memory and removed from entityBlock.
	for (vector<CRE_Entity*>::iterator itr = entityBlock.begin(); itr < entityBlock.end(); itr++)
	{
		if (e == (*itr))
		{
			delete* itr;

			entityBlock.erase(itr);
			break;
		}
	}
}

unsigned int allocateEntity(const CRE_EntityType& type)
{
	return allocateEntityPtr(type)->getEntityID();
}

CRE_Entity* allocateEntityPtr(const CRE_EntityType& type)
{
	//allocates memory to a new entity in entityBlock
	//then returns the ID of the allocated ID

	CRE_Entity* entity;

	CRE_EntityData tempData;

	switch (type)
	{
	default:
	case PACMAN:
		entity = new CRE_Entity;
		entityBlock.push_back(entity);
		entity->setTexture(e_Pacman::imageDat::pacmanSprite);
		entity->setPosition(12, 36, 0);
		tempData.componentData.pacman = e_Pacman::entityData::pacmanData;
		entity->setEntityData(tempData);
		entity->setEntityType(PACMAN);
		e_Pacman::logic::stop(entity->getEntityID());
		break;

	case GHOST:
		break;

	case DOT:
		break;

	case SUPER_DOT:
		break;

	case TEXT:
		break;

	case TILE:
		entity = new CRE_Entity;
		entity->setEntityType(TILE);
		entityBlock.push_back(entity);

	}

	return entityBlock.back();
}

CRE_Entity* entityFromID(const unsigned int& id)
{
	//cycles through entityBlock until an entity is found whose internal ID
	//equals the passed ID. A pointer to this entity is returned.
	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		if (id == entityBlock[i]->getEntityID())
			return entityBlock[i];
	}

	//Case for if no entity with the passed ID can be found.
	//Will return NULL in this case.
	return NULL;
}

void sortEntities()
{
	sort(entityBlock);
}