#pragma once
#include "Vector.h"
#include <list>
#include <vector>
#include "Entity.h"
namespace Sim {
	class GridNode
	{
	public:
		//Sim::Vector Size;
		Vector<int> Location;
		//Local list of entities 
		std::vector<Entity*> EntityList;
		std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> NearEntityList;
		GridNode();
		GridNode(Vector<int> loc);
		~GridNode();
		void AddEntity(Entity * entity);
		void RemoveEntity(Entity * entity);
		std::vector<Entity*> &GetEntities();
	};
}
