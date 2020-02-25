#include "entityHandler.h"

extern vector<CRE_Entity*> entityBlock;

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

unsigned int allocateEntity(const CRE_EntityType& type)
{
	//allocates memory to a new entity in entityBlock
	//then returns the ID of the allocated ID

	switch (type)
	{
	default:
	case test:
		entityBlock.push_back(new CRE_Entity);
		break;
	}

	return entityBlock.back()->getEntityID();
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