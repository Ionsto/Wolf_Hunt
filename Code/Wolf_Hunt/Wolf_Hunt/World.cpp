#include "World.h"
#include "EntityGrass.h"
#include <math.h>
#include "EntitySheep.h"
#include "EntityWolf.h"
#include <thread>


Sim::World::World() : WorldRender()
{
	WorldRender.WorldSize = WorldSize;
	for (int i = 0; i < GridCount; ++i)
	{
		for (int v = 0; v < GridCount; ++v)
		{
			this->WorldGrid[i][v] = GridNode(Vector<int>(i, v));
		}
	}
	//Init near grid refrences
	for (int i = 0; i < GridCount; ++i)
	{
		for (int v = 0; v < GridCount; ++v)
		{
			const int LookUpDistance = 2;
			auto Entities = std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>>();
			for (int x = i; x <= i + LookUpDistance; ++x)
			{
				for (int y = v; y <= v + LookUpDistance; ++y)
				{
					if (x >= 0 && x < GridCount)
					{
						if (y >= 0 && y < GridCount)
						{
							auto NEntity = std::ref(WorldGrid[x][y].GetEntities());
							Entities.emplace_back(NEntity);
							//Entities.insert(Entities.end(), WorldGrid[idloc.X][idloc.Y].GetEntities().begin(), WorldGrid[idloc.X][idloc.Y].GetEntities().end());
						}
					}
				}
			}
			this->WorldGrid[i][v].NearEntityList = Entities;
		}
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
	WorldRender.RenderScene();
#pragma omp parallel for
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
#pragma omp parallel for
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
inline static void ResolveEntEntCollision(Sim::Entity * entA, Sim::Entity * entB)
{
	//Collision detect
	Sim::Vector<float> Diff = entA->Pos - entB->Pos;
	float SqrdDistacnce = Diff.DotXY(Diff);
	float CombinedSize = entA->Size + entB->Size;
	if (SqrdDistacnce < CombinedSize * CombinedSize)
	{
		//Collision happened
		Sim::Vector<float> VAB = (entA->Pos - entA->PosOld) - (entB->Pos - entB->PosOld);
		const float e = 1;
		float j = (-(1 + e) * VAB.DotXY(Diff)) / (SqrdDistacnce * (1 / entA->Mass + 1 / entB->Mass));

		float sqrtDistance = sqrtf(SqrdDistacnce);
		Sim::Vector<float> Translate = (Diff / sqrtDistance) * (CombinedSize - sqrtDistance);
		//Move them to touching
		Diff = Diff / sqrtDistance;
		entA->Pos += Translate * 0.5;
		entB->Pos -= Translate * 0.5;
		entA->PosOld += Translate * 0.5;
		entB->PosOld -= Translate * 0.5;
		entA->PosOld -= Diff * j;
		entB->PosOld += Diff * j;
		entA->Collision(entB);
		entB->Collision(entA);
	}
}
inline static void ResolveCollisionsListPairs(std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> & NearEntiteslists, int j)
{
	auto outerlist = NearEntiteslists[0].get();
	for (int x = 0; x < outerlist.size() - 1; ++x)
	{
		if (outerlist[x]->Alive)
		{
			for (int z = x + 1; z < outerlist.size(); ++z)
			{
				if (outerlist[z]->Alive)
				{
					ResolveEntEntCollision(outerlist[x], outerlist[z]);
				}
			}
		}
	}
}
void Sim::World::ResolveCollisions()
{
	#pragma omp parallel for
	for (int XGrid = 0; XGrid < GridCount; ++XGrid)
	{
		for (int YGrid = 0; YGrid < GridCount; ++YGrid)
		{
			std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> & NearEntiteslist = GetNearbyEntities(Vector<int>(XGrid, YGrid));
			int i = 0;
			for (int j = 0; j < NearEntiteslist.size(); ++j)
			{
				if (i != j)
				{
					//Check n^2 comparisons, each entity on each entity
					ResolveCollisionsListed(NearEntiteslist[i], NearEntiteslist[j]);
				}
				else
				{
					//Check 
					auto outerlist = NearEntiteslist[i].get();
					if (outerlist.size() > 0)
					{
						for (int x = 0; x < outerlist.size() - 1; ++x)
						{
							if (outerlist[x]->Alive)
							{
								for (int z = x + 1; z < outerlist.size(); ++z)
								{
									if (outerlist[z]->Alive)
									{
										ResolveEntEntCollision(outerlist[x], outerlist[z]);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
inline void Sim::World::ResolveCollisionsListed(std::vector<Entity *> & lista, std::vector<Entity*> & listb)
{
	if (listb.size() > 0)
	{
		for (int i = 0; i < lista.size(); ++i)
		{
			if (lista[i]->Alive)
			{
				for (int j = 0; j < listb.size(); ++j)
				{
					if (listb[j]->Alive && lista[i]->Alive)
					{
						ResolveEntEntCollision(lista[i], listb[j]);
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
	if (!ent->ValidObject)
	{
		std::cout << "Added invalid object\n";
		return -1;
	}
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
std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>>& Sim::World::GetNearbyEntities(Vector<int> gridid)
{
	return WorldGrid[gridid.X][gridid.Y].NearEntityList;
}
Sim::Entity * Sim::World::GetClosestEntity(Entity * ThisEntity)
{
	auto complist = GetNearbyEntities(ThisEntity->GridID);
	Entity * EntityClosest = nullptr;
	float dist = 0;
	for each (auto slist in complist)
	{
		auto iter = std::min_element(slist.get().begin(), slist.get().end(), [=](Entity * a, Entity * b) -> bool {
			//Push the search entity to the back
			if (a == ThisEntity) { return false; }
			if (b == ThisEntity) { return true; }
			Vector<float> dissA = a->Pos - ThisEntity->Pos;
			Vector<float> dissB = b->Pos - ThisEntity->Pos;
			return dissA.DotXY(dissA) < dissB.DotXY(dissB);
		});
		if (iter != slist.get().end() && *iter != ThisEntity)
		{
			if (EntityClosest == nullptr)
			{
				EntityClosest = *iter;
				Vector<float> dissA = EntityClosest->Pos - ThisEntity->Pos;
				dist = dissA.DotXY(dissA);
			}
			else
			{
				auto entb = *iter;
				Vector<float> dissA = entb->Pos - ThisEntity->Pos;
				if (dissA.DotXY(dissA) < dist)
				{
					EntityClosest = entb;
					dist = dissA.DotXY(dissA);
				}
			}
		}
	}
	return EntityClosest;
}