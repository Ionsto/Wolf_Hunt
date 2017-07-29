#pragma once
#include "Entity.h"
namespace Sim {
	class EntityLiving : public Sim::Entity
	{
	public:
		float Health;
		bool Alive;
		EntityLiving(Sim::World * wrld);
		~EntityLiving();
		virtual void Update() override;
		virtual void UpdateAI();
	};
};