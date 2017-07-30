#pragma once
#include "EntityLiving.h"
namespace Sim {
	class EntityWolf :
		public EntityLiving
	{
	public:
		Vector<float> TargetLocation;
		EntityWolf(World * world);
		~EntityWolf();
		virtual void Update() override;
		virtual void UpdateAI() override;
		virtual void SetLocation(Vector<float> Pos) override;
	};
}

