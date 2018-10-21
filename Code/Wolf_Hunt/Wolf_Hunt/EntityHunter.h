#pragma once
#include "Entity.h"
#include "EntityLiving.h"
#include "EntityCorpse.h"
#include "Constraint.h"
#include <memory>

namespace Sim {
	class EntityHunter : public EntityLiving
	{
	public:
		float EatSpeed = 40;
		bool Attacking = false;
		bool Eating = false;
		float EatDistance;
		float HoldDistance;
		std::unique_ptr<Constraint> EatingConstraint;
		std::unique_ptr<Constraint> HoldConstraint;
		EntityHunter(Sim::World * wrld);
		virtual ~EntityHunter();
		virtual void Update() override;
		void TryHold(Entity * entity);
		void TryEat(Entity * entity);
		void UpdateConstraints();
	};
}

