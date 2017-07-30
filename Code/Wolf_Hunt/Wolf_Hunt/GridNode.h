#pragma once
#include "Vector.h"
#include <list>
#include "Entity.h"
namespace Sim {
	class GridNode
	{
	public:
		//Sim::Vector Size;
		Vector<int> Location;
		//Local list of entities 
		std::list<Entity*> EntityList;
		GridNode();
		GridNode(Vector<int> loc);
		~GridNode();
		void AddEntity(Entity * entity);
		void RemoveEntity(Entity * entity);
		std::list<Entity*> GetEntities();
	};
}
