#pragma once
#include "Entity.h"
#include "GridNode.h"
#include <Memory>
#include <Array>
namespace Sim {
	class World
	{
	public:
		int WorldSize;
		int GridCount;
		int GridSize;
		static const int EntityCount = 5000;
		Sim::GridNode ** WorldGrid;
		//Represents the master list of all entities
		std::array<std::unique_ptr<Sim::Entity>, EntityCount> EntityList;
		Vector<int> GetGridIDs(Vector<float> Pos);
		World();
		~World();
		//Single tick happens
		void Update();
		//Keep the grid datastructure correct
		void ResolveGrid();
		//Resolve all entity->entity collisions
		void ResolveCollisions();
		int AddEntity(std::unique_ptr<Entity> ent);
		std::list<Entity *> GetNearbyEntities(Vector<int> gridid);
	};
}