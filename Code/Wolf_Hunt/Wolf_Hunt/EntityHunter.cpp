#include "EntityHunter.h"
#include "World.h"
#include "Entity.h"
#include <iostream>

Sim::EntityHunter::EntityHunter(World * world) : EntityLiving(world)
{
	EatSpeed = 5000;
	HoldConstraint = Constraint();
	EatingConstraint = Constraint();
	HoldConstraint.entityA = this;
	EatingConstraint.entityA = this;
	EatDistance = 25;
	HoldDistance = 25;
}


Sim::EntityHunter::~EntityHunter()
{
}
void Sim::EntityHunter::Update()
{
	EntityLiving::Update();
	UpdateConstraints();
}

void Sim::EntityHunter::TryHold(Entity * entity)
{
	if (dynamic_cast<EntityLiving*>(entity) != nullptr)
	{
		//If the held entity is nonexistant & we currently arn't holding entity
		if (HoldConstraint.entityB != entity)
		{
			//Generate constraint
			Vector<float> Diff = Pos - entity->Pos;
			float DistSqrd = Diff.Dot(Diff);
			std::cout << sqrt(DistSqrd) << std::endl;
			if (DistSqrd < HoldDistance * HoldDistance)
			{
				HoldConstraint.SetEntityB(entity);
				HoldConstraint.Length = sqrt(DistSqrd);

			}
		}
	}
}
void Sim::EntityHunter::TryEat(Entity * entity)
{
	if (dynamic_cast<EntityLiving*>(entity) != nullptr)
	{
		//If the held entity is nonexistant & we currently arn't holding entity
		if (EatingConstraint.entityB != entity)
		{
			//Generate constraint
			Vector<float> Diff = Pos - entity->Pos;
			float DistSqrd = Diff.Dot(Diff);
			if (DistSqrd < EatDistance * EatDistance)
			{
				EatingConstraint.SetEntityB(entity);
				EatingConstraint.Length = sqrt(DistSqrd);
			}
		}
	}
}
void Sim::EntityHunter::UpdateConstraints()
{
	if (EatingConstraint.entityB != nullptr)
	{
		//Do some eating!
		float Delta = fmin(((EntityCorpse*)EatingConstraint.entityB)->Energy, EatSpeed) * WorldObj->DeltaTime;
		this->Energy += Delta;
		((EntityCorpse*)EatingConstraint.entityB)->Energy -= Delta;
	}
	else
	{
		Eating = false;
	}
}