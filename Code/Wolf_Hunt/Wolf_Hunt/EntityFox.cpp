#include "EntityFox.h"
#include "EntityCorpse.h"
#include "EntitySheep.h"
#include "World.h"
#include <algorithm>

Sim::EntityFox::EntityFox(World * world) : EntityLiving(world)
{
	Type = Fox;
	MaxAccelerationForward = 500;
	MaxAccelerationBack = 100;
	MaxRotAcceleration = 100;
	RotAcceleration = 20;
	EnergyLossPerAcc = 2 / 500.0;
	Attacking = true;
	TargetLocation = Vector<float>(-1, -1);
	this->AIState = EntityFox::States::Chase;
}


Sim::EntityFox::~EntityFox()
{
}

void Sim::EntityFox::Update()
{
	if (OnFloor)
	{
		if (TargetLocation.X != -1 && TargetLocation.Y != -1)
		{
			Vector<float> Diff = TargetLocation - Pos;
			Diff = Diff * 5;
			float CloseDistSqrd = 20 * 20;
			if (Diff.Dot(Diff) > CloseDistSqrd)
			{
				ApplyWalkForce(Diff);
				TargetRotation = atan2f(Diff.Y, Diff.X);
			}
			else
			{
				TargetLocation.X = -1;
				TargetLocation.Y = -1;
			}
		}
	}
	EntityLiving::Update();
}
void Sim::EntityFox::UpdateAI()
{
	//Update
	auto EntityClosest = WorldObj->GetClosestEntity(this);
	enum
	{
		Chase, Eat
	};
	Eating = false;
	switch (AIState)
	{
	case Chase:
		if (EntityClosest != NULL)
		{
			this->TargetLocation = EntityClosest->Pos;
		}
		break;
	case Eat:
		Eating = true;
		break;
	}
}

void Sim::EntityFox::Collision(Entity * ent)
{
	if (dynamic_cast<EntitySheep*>(ent) != NULL)
	{
		if (Attacking)
		{
			ent->Kill();
		}
	}
	if (dynamic_cast<EntityCorpse*>(ent) != NULL)
	{
		if (Attacking)
		{
			if (dynamic_cast<EntityCorpse*>(ent) != NULL)
			{
				float Delta = fmin(((EntityCorpse*)ent)->Energy, EatSpeed) * WorldObj->DeltaTime;
				Energy += Delta;
				((EntityCorpse*)ent)->Energy -= Delta;
			}
		}
	}
}