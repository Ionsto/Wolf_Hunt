#pragma once
#include "Entity.h"
namespace Sim {
	class EntityGrass :
		public Entity
	{
	public:
		int GrowthCount = 0;
		int MaxGrowthCount = 1000;
		int EnergyPerEat = 50;
		bool Grown = false;
		EntityGrass(World * world);
		~EntityGrass();
		virtual void Update() override;
	};
}

