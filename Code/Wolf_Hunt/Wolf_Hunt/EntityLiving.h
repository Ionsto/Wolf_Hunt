#pragma once
#include "Entity.h"
namespace Sim {
	class EntityLiving : public Sim::Entity
	{
	public:
		float MaxSpeed = 10;
		float MaxAcceleration = 5;
		enum EntityTypes {
		Wolf,Sheep,Other
		} Type;
		float Health;
		EntityLiving(Sim::World * wrld);
		~EntityLiving();
		virtual void Update() override;
		virtual void UpdateAI();
	};
};