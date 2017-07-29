#include "World.h"



Sim::World::World()
{
}


Sim::World::~World()
{
}

void Sim::World::Update()
{
	//Update Grid locations, shuffle them the correct grid location
	ResolveGrid();

	ResolveCollisions();
}

void Sim::World::ResolveGrid()
{

}

void Sim::World::ResolveCollisions() 
{

}