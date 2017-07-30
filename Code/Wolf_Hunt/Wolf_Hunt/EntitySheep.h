#pragma once
#include "EntityLiving.h"
#include "AIBoids.h"
namespace Sim {
	class EntitySheep :
		public EntityLiving
	{
	public:
		AIBoids BoidsInstance;
		EntitySheep(World * world);
		~EntitySheep();
		virtual void Update() override;
		virtual void UpdateAI() override;
	};
}

