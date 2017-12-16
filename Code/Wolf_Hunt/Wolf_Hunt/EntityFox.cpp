#include "EntityFox.h"
#include "EntityCorpse.h"
#include "EntitySheep.h"
#include "World.h"
#include <algorithm>
#include "Vector.h"

Sim::EntityFox::EntityFox(World * world) : EntityHunter(world)
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
		else
		{
			float OffsetEdge = 10;
			TargetLocation += Vector<float>((rand() % 200) - 100, (rand() % 200) - 100,0);
			TargetLocation.X = std::min<float>(std::max<float>(OffsetEdge, TargetLocation.X), WorldObj->WorldSize - OffsetEdge);
			TargetLocation.Y = std::min<float>(std::max<float>(OffsetEdge, TargetLocation.Y), WorldObj->WorldSize - OffsetEdge);
		}
	}
	EntityHunter::Update();
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
		if (EntityClosest != nullptr)
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
	if (dynamic_cast<EntitySheep*>(ent) != nullptr)
	{
		if (Attacking)
		{
			ent->Kill();
		}
	}
	if (dynamic_cast<EntityCorpse*>(ent) != nullptr)
	{
		if (Attacking)
		{
			if (dynamic_cast<EntityCorpse*>(ent) != nullptr)
			{
				float Delta = fmin(((EntityCorpse*)ent)->Energy, EatSpeed) * WorldObj->DeltaTime;
				Energy += Delta;
				((EntityCorpse*)ent)->Energy -= Delta;
			}
		}
	}
}