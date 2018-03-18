#pragma once
#include "Entity.h"
namespace Sim {
	class EntityGrass :
		public Entity
	{
	public:
		float GrowthCount = 0;
		float MaxGrowthCount = 1000;
		int EnergyPerEat = 50;
		bool Grown = false;
		EntityGrass(World * world);
		virtual ~EntityGrass();
		virtual void Update() override;
	};
}

