#pragma once
#include "Vector.h"
#include "Entity.h"
#include <vector>
namespace Sim {
	class AIBoids
	{
	public:
		AIBoids();
		~AIBoids();
		float Repulsion;
		float Clump;
		float Coheasion;
		float Flee;
		Vector<float> CalculateAcc(Entity * Self,std::vector<Entity*> list);
	private:
		Vector<float> CalculateRepulsion(Entity * Self,std::vector<Entity*> list);
		Vector<float> CalculateClump(Entity * Self,std::vector<Entity*> list);
		Vector<float> CalculateCoheasion(Entity * Self, std::vector<Entity*> list);
		Vector<float> CalculateFlee(Entity * Self, std::vector<Entity*> list);

	};
}
