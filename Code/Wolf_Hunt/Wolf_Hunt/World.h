#pragma once
#include "Entity.h"
#include "GridNode.h"
#include <Memory>
#include <Array>
namespace Sim {
	class World
	{
	public:
		static const int GridCount = 10;
		static const int EntityCount = 5000;
		std::array<std::array<Sim::GridNode, GridCount>, GridCount> WorldGrid;
		//Represents the master list of all entities
		std::array<std::unique_ptr<Sim::Entity>, EntityCount> EntityList;
		World();
		~World();
		//Single tick happens
		void Update();
		//Keep the grid datastructure correct
		void ResolveGrid();
		//Resolve all entity->entity collisions
		void ResolveCollisions();
	};
}