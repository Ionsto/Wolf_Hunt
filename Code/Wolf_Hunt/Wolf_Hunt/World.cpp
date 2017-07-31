#include "World.h"
#include "EntityGrass.h"
#include <math.h>

Sim::World::World()
{
	GridCount = 10;
	WorldSize = 1000;
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
		//int id = AddEntity(std::make_unique<EntityGrass>(EntityGrass(this)));
		//EntityList[id]->Pos = Vector<float>(rand() % WorldSize, rand() % WorldSize);
		//EntityList[id]->PosOld = EntityList[id]->Pos;
	}
	ResolveGrid();
	DeltaTime = 0.001;
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
				WorldGrid[EntityList[i]->GridID.X][EntityList[i]->GridID.Y].RemoveEntity(EntityList[i].get());
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
				EntityList[i]->GridID = NewGridID;
			}
		}
	}
}

void Sim::World::ResolveCollisions() 
{
	for (int XGrid = 0; XGrid < GridCount; ++XGrid)
	{
		for (int YGrid = 0; YGrid < GridCount; ++YGrid)
		{
			std::vector<Entity *> NearEntites = GetNearbyEntities(Vector<int>(XGrid,YGrid));
			if(NearEntites.size() > 0)
			{
				for (int i = 0; i < NearEntites.size() - 1; ++i)
				{
					if (NearEntites[i]->Alive)
					{
						for (int j = i + 1; j < NearEntites.size(); ++j)
						{
							if (NearEntites[j]->Alive)
							{
								Entity * entA = NearEntites[i];
								Entity * entB = NearEntites[j];
								//Collision detect
								Vector<float> Diff = entA->Pos - entB->Pos;
								float SqrdDistacnce = Diff.Dot(Diff);
								float CombinedSize = entA->Size + entB->Size;
								if (SqrdDistacnce < CombinedSize * CombinedSize)
								{
									//Collision happened
									Vector<float> VAB = (entA->Pos - entA->PosOld) - (entB->Pos - entB->PosOld);
									const float e = 1;
									float j = (-(1 + e) * VAB.Dot(Diff)) / (SqrdDistacnce * (1 / entA->Mass + 1 / entB->Mass));

									float sqrtDistance = sqrtf(SqrdDistacnce);
									Vector<float> Translate = (Diff / sqrtDistance) * (CombinedSize - sqrtDistance);
									//Move them to touching
									Diff = Diff / sqrtDistance;
									entA->Pos += Translate * 0.5;
									entB->Pos -= Translate * 0.5;
									entA->PosOld += Translate * 0.5;
									entB->PosOld -= Translate * 0.5;
									entA->PosOld -= Diff * j;
									entB->PosOld += Diff * j;
								}
							}
						}
					}
				}
			}
		}
	}
}
Sim::Vector<int> Sim::World::GetGridIDs(Vector<float> pos)
{
	auto loc = Vector<int>(floorf(pos.X / this->GridSize), floorf(pos.Y / GridSize));
	loc.X = std::min(loc.X, GridCount - 1);
	loc.Y = std::min(loc.Y, GridCount - 1);
	loc.X = std::max(loc.X, 0);
	loc.Y = std::max(loc.Y, 0);
	return loc;
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
std::vector<Sim::Entity *> Sim::World::GetNearbyEntities(Vector<int> gridid)
{
	const int LookUpDistance = 2;
	std::vector<Sim::Entity*> Entities = std::vector<Sim::Entity*>();
	for (int x = -LookUpDistance; x <= LookUpDistance; ++x)
	{
		for (int y = -LookUpDistance; y <= LookUpDistance; ++y)
		{
			Vector<int> idloc = gridid + Vector<int>(x, y);
			if (idloc.X >= 0 && idloc.X < GridCount)
			{
				if (idloc.Y >= 0 && idloc.Y < GridCount)
				{
					std::vector<Sim::Entity*> NEntity = WorldGrid[idloc.X][idloc.Y].GetEntities();
					Entities.insert(std::end(Entities), std::begin(NEntity), std::end(NEntity));
					//Entities.insert(Entities.end(), WorldGrid[idloc.X][idloc.Y].GetEntities().begin(), WorldGrid[idloc.X][idloc.Y].GetEntities().end());
				}
			}
		}
	}
	return Entities;
}