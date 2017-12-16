#pragma once
#include "Entity.h"
#include "EntityLiving.h"
#include "EntityCorpse.h"
#include "Constraint.h"

namespace Sim {
	class EntityHunter : public EntityLiving
	{
	public:
		float EatSpeed = 100;
		bool Attacking = false;
		bool Eating = false;
		float EatDistance;
		float HoldDistance;
		Constraint EatingConstraint;
		Constraint HoldConstraint;
		EntityHunter(Sim::World * wrld);
		~EntityHunter();
		virtual void Update() override;
		void TryHold(Entity * entity);
		void TryEat(Entity * entity);
		void UpdateConstraints();
	};
}

