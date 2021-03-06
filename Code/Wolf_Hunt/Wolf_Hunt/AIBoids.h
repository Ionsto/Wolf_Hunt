#pragma once
#include "Vector.h"
#include "Entity.h"
#include <vector>
namespace Sim {
	class AIBoids
	{
	public:
		AIBoids();
		virtual ~AIBoids();
		float Repulsion;
		float Clump;
		float Coheasion;
		float Flee;
		float WallAversion;
		Vector<float> CalculateAcc(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list);
	private:
		Vector<float> CalculateRepulsion(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list);
		Vector<float> CalculateClump(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list);
		Vector<float> CalculateCoheasion(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list);
		Vector<float> CalculateFlee(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list);
		Vector<float> CalculateWallAversion(Entity * Self);

	};
}
