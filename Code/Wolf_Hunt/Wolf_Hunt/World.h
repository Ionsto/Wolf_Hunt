#pragma once
#include "Entity.h"
#include "SystemRender.h"
#include "SystemCollision.h"
#include "SystemEntityAI.h"
#include "GridNode.h"
#include <Memory>
#include <Array>
namespace Sim {
	class World
	{
	public:
		float DeltaTime = 1/60;
		static const int GridCount = 8;
		static const int GridSize = 200;
		static const int WorldSize = GridCount*GridSize;
		static const int EntityCount = 500;
		float Gravity = 9.8;

		SystemRender WorldRender;
		SystemCollision WorldCollision;
		SystemEntityAI WorldAI;


		std::array<std::array<Sim::GridNode, GridCount>, GridCount> WorldGrid;
		//Represents the master list of all entities
		std::array<std::unique_ptr<Sim::Entity>, EntityCount> EntityList;
		//static void ResolveCollisionsListPairs(std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> & NearEntiteslists, int j);
		Vector<int> GetGridIDs(Vector<float> Pos);
		World();
		virtual ~World();
		//Single tick happens
		void Update();
		//Keep the grid datastructure correct
		void ResolveGrid();
		//Resolve all entity->entity collisions
		void ResolveCollisions();
		void ResolveCollisionsListed(std::vector<Entity *> &, std::vector<Entity*> &);
		//static void ResolveEntEntCollision(Entity * entA,Entity * EntB);
		int AddEntity(std::unique_ptr<Entity> ent);
		std::vector<std::reference_wrapper<std::vector<Entity *>>> & GetNearbyEntities(Vector<int> gridid);
		Entity * GetClosestEntity(Entity * ThisEnt);
	};
}