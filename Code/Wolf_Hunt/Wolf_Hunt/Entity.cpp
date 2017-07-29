#include "Entity.h"
#include "World.h"


Entity::Entity(World * wrld)
{
	this->WorldObj = wrld;
}


Entity::~Entity()
{
}

void Entity::Update()
{
}