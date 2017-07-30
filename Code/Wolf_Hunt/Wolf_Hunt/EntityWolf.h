#pragma once
#include "EntityLiving.h"
namespace Sim {
	class EntityWolf :
		public EntityLiving
	{
	public:
		EntityWolf(World * world);
		~EntityWolf();
		virtual void Update() override;
		virtual void UpdateAI() override;
	};
}

