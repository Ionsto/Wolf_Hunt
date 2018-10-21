#include "EntityHunter.h"
#include "World.h"
#include "Entity.h"
#include <iostream>

Sim::EntityHunter::EntityHunter(World * world) : EntityLiving(world)
{
	HoldConstraint = std::make_unique<Constraint>();
	EatingConstraint = std::make_unique<Constraint>();
	HoldConstraint->entityA = this;
	EatingConstraint->entityA = this;
	HoldConstraint->WorldObj = world;
	EatingConstraint->WorldObj = world;
	EatDistance = 27;
	HoldDistance = 27;
}


Sim::EntityHunter::~EntityHunter()
{
}

void Sim::EntityHunter::Update()
{
	UpdateConstraints();
	EntityLiving::Update();
}

void Sim::EntityHunter::TryHold(Entity * entity)
{
	if (dynamic_cast<EntityLiving*>(entity) != nullptr)
	{
		//If the held entity is nonexistant & we currently arn't holding entity
		if (HoldConstraint->entityB != entity)
		{
			//Generate constraint
			Vector<float> Diff = Pos - entity->Pos;
			float DistSqrd = Diff.DotXY(Diff);
			std::cout << sqrt(DistSqrd) << std::endl;
			if (DistSqrd < HoldDistance * HoldDistance)
			{
				HoldConstraint->SetEntityB(entity);
				HoldConstraint->Length = sqrt(DistSqrd);
			}
		}
	}
}
void Sim::EntityHunter::TryEat(Entity * entity)
{
	if (dynamic_cast<EntityCorpse*>(entity) != nullptr)
	{
		//If the held entity is nonexistant & we currently arn't holding entity
		if (EatingConstraint->entityB != entity)
		{
			//Generate constraint
			Vector<float> Diff = Pos - entity->Pos;
			float DistSqrd = Diff.DotXY(Diff);
			std::cout << DistSqrd <<"\n";
			if (DistSqrd < EatDistance * EatDistance)
			{
				std::cout << "Entity eaten\n";
				EatingConstraint->SetEntityB(entity);
				EatingConstraint->Length = sqrt(DistSqrd);
			}
		}
	}
}
void Sim::EntityHunter::UpdateConstraints()
{
	EatingConstraint->Update();
	HoldConstraint->Update();
	
	if (EatingConstraint->entityB != nullptr)
	{
		//Do some eating!
		float Delta = fmin(((EntityCorpse*)EatingConstraint->entityB)->Energy, EatSpeed * WorldObj->DeltaTime);
		this->Energy += Delta;
		((EntityCorpse*)EatingConstraint->entityB)->Energy -= Delta;
		std::cout << "Eating thing for delta: " << Delta << "\n";
		//std::cout << "Delta:"<<Delta <<" full:"<< ((EntityCorpse*)EatingConstraint->entityB)->Energy <<"\n";
	}
	else
	{
		Eating = false;
	}
}