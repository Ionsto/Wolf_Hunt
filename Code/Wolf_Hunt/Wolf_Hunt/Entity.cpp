#include "Entity.h"
#include "World.h"


Sim::Entity::Entity(World * wrld)
{
	this->WorldObj = wrld;
}


Sim::Entity::~Entity()
{

}

void Sim::Entity::Update()
{

}