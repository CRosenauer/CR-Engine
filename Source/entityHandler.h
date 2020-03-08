#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H

#include <vector>

#include "entity.h"

//cycles through entityBlock until entity is found whose ID equals the passed ID
//deallocates said entity from memory and removes the entity* from the vector
void deleteEntity(const unsigned int& entityID);

//pushes a new entity to the entity vector and sets it to defined
//returns the ID of the entity
unsigned int allocateEntity(const CRE_EntityType& type);

//cycles through entityBlock until an entity is found whose internal ID
//matches the passed ID.
//function returns the pointer to said entity.
//if no entity with the passed ID can be found function returns NULL.
CRE_Entity* entityFromID(const unsigned int& id);

#endif //ENTITYHANDLER_H