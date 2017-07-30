#include "World.h"
#include "EntityGrass.h"


Sim::World::World()
{
	GridCount = 10;
	WorldSize = 500;
	GridSize = WorldSize / GridCount;
	this->WorldGrid = new GridNode*[GridCount];
	for (int i = 0; i < GridCount; ++i)
	{
		this->WorldGrid[i] = new GridNode[GridCount];
		for (int v = 0; v < GridCount; ++v)
		{
			this->WorldGrid[i][v] = GridNode(Vector<int>(i,v));
		}
	}
	for (int i = 0; i < 2000;++i)
	{
		int id = AddEntity(std::make_unique<EntityGrass>(EntityGrass(this)));
		EntityList[id]->Pos = Vector<float>(rand() % WorldSize, rand() % WorldSize);
		EntityList[id]->PosOld = EntityList[id]->Pos;
	}
	ResolveGrid();
}


Sim::World::~World()
{
}

void Sim::World::Update()
{
	//Update Grid locations, shuffle them the correct grid location
	ResolveGrid();
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i])
		{
			if (EntityList[i]->Alive)
			{
				EntityList[i]->Update();
			}
			else
			{
				EntityList[i].reset();
			}
		}
	}
	ResolveCollisions();
}

void Sim::World::ResolveGrid()
{
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i])
		{
			//Resolve grid
			Vector<int> NewGridID = GetGridIDs(EntityList[i]->Pos);
			if (NewGridID != EntityList[i]->GridID)
			{
				//Update Grid
				WorldGrid[NewGridID.X][NewGridID.Y].AddEntity(EntityList[i].get());
				WorldGrid[EntityList[i]->GridID.X][EntityList[i]->GridID.Y].RemoveEntity(EntityList[i].get());
			}
		}
	}
}

void Sim::World::ResolveCollisions() 
{

}
Sim::Vector<int> Sim::World::GetGridIDs(Vector<float> pos)
{
	return Vector<int>(floorf(pos.X / this->GridSize),floorf(pos.Y / GridSize));
}
int Sim::World::AddEntity(std::unique_ptr<Entity> ent)
{
	for (int i = 0; i < EntityCount; ++i)
	{
		if (!EntityList[i])
		{
			ent->Id = i;
			ent->GridID = GetGridIDs(ent->Pos);
			EntityList[i] = std::move(ent);
			WorldGrid[EntityList[i]->GridID.X][EntityList[i]->GridID.Y].AddEntity(EntityList[i].get());
			return i;
		}
	}
	return -1;
}
std::list<Sim::Entity *> Sim::World::GetNearbyEntities(Vector<int> gridid)
{
	std::list<std::array<int,2>> offsets = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{ 1,-1 },{ 1,0 },{ 1,1 } };
	std::list<Sim::Entity*> Entities = std::list<Sim::Entity*>();
	for each (auto var in offsets)
	{
		Vector<int> idloc = gridid + Vector<int>(var[0], var[1]);
		if (idloc.X >= 0 && idloc.X < GridCount)
		{
			if (idloc.Y >= 0 && idloc.Y < GridCount)
			{
				Entities.splice(Entities.end(), WorldGrid[idloc.X][idloc.Y].GetEntities());
			}
		}
	}
	return Entities;
}