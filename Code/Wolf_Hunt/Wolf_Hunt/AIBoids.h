#pragma once
#include "Vector.h"
#include "Entity.h"
#include <list>
namespace Sim {
	class AIBoids
	{
	public:
		AIBoids();
		~AIBoids();
		float Repulsion;
		float Clump;
		float Coheasion;
		Vector<float> CalculateAcc(Entity * Self,std::list<Entity*> list);
	private:
		Vector<float> CalculateRepulsion(Entity * Self,std::list<Entity*> list);
		Vector<float> CalculateClump(Entity * Self,std::list<Entity*> list);
		Vector<float> CalculateCoheasion(Entity * Self,std::list<Entity*> list);

	};
}
