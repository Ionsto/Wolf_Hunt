#include "EntityWolf.h"
#include "EntitySheep.h"
#include "EntityCorpse.h"
#include "World.h"

Sim::EntityWolf::EntityWolf(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Wolf;
	TargetLocation = Vector<float>(-1,-1); 
	Size = 10;
	MaxAccelerationForward = 500;
	MaxAccelerationBack = 200;
	LeapPower = 7000;
	LeapPowerVertical = 300;
	EnergyLossPerAcc = 2 / 500.0;
	BiteConstraint = Constraint();
	BiteConstraint.WorldObj = wrld;
}


Sim::EntityWolf::~EntityWolf()
{

}

void Sim::EntityWolf::Update()
{
	EntityLiving::Update();
	LeapCooldownTimer -= WorldObj->DeltaTime;
	if (LeapCooldownTimer < 0)
	{
		LeapCooldownTimer = 0;
	}
	BiterCooldownTimer += WorldObj->DeltaTime;
	if (BiterCooldownTimer > BiteCooldown)
	{
		BiterCooldownTimer = BiteCooldown;
	}
	if (BiterCooldownTimer > BiteTime)
	{
		Attacking = false;
	}
	if (OnFloor)
	{
		if (Leaping) 
		{
			Attacking = false;
		}
		if (TargetLocation.X != -1 && TargetLocation.Y != -1)
		{
			Vector<float> Diff = TargetLocation - Pos;
			Diff = Diff * 5;
			float CloseDistSqrd = 20 * 20;
			if (Diff.Dot(Diff) > CloseDistSqrd)
			{
				TargetAcceleration = Diff;
				//ApplyWalkForce(Diff);
				TargetRotation = atan2f(Diff.Y, Diff.X);
			}
			else
			{
				TargetAcceleration = Vector<float>();
				TargetLocation.X = -1;
				TargetLocation.Y = -1;
			}
		}
	}
	if (Grabbing)
	{
		BiteConstraint.Update();
	}
}
void Sim::EntityWolf::UpdateAI()
{
	EntityLiving::UpdateAI();
}

void Sim::EntityWolf::SetLocation(Vector<float> pos)
{
	Entity::SetLocation(pos);
	TargetLocation = pos;
}

void Sim::EntityWolf::UseLeap()
{
	if (LeapCooldownTimer <= 0)
	{
		//Leap
		LeapCooldownTimer = LeapCooldown;
		Vector<float> force = Vector<float>(cos(Rot) * LeapPower, sin(Rot) * LeapPower, LeapPowerVertical);
		ApplyForce(force);
		Energy -= sqrt(force.Dot(force)) * EnergyLossPerAcc;
		Attacking = true;
		Leaping = true;
		OnFloor = false;
	}
}
void Sim::EntityWolf::UseBite()
{
	BiterCooldownTimer = 0;
	Attacking = true;
	Eating = true;
}
void Sim::EntityWolf::UseGrab()
{
	if (Grabbing)
	{
		Grabbing = false;
	}
	else
	{
		//Attempt a grab
		auto EntityClosest = WorldObj->GetClosestEntity(this);
		if (EntityClosest != NULL)
		{
			Vector<float> Diff = Pos - EntityClosest->Pos;
			float DistSqrd = Diff.Dot(Diff);
			const float DistanceToGrab = 25;
			if (DistSqrd < DistanceToGrab * DistanceToGrab)
			{
				BiteConstraint.entityA = this;
				BiteConstraint.entityB = EntityClosest;
				Grabbing = true;
				BiteConstraint.Length = sqrt(DistSqrd);
			}
		}
	}
}

void Sim::EntityWolf::Collision(Entity * entity)
{
	if (dynamic_cast<EntitySheep*>(entity) != NULL)
	{
		if (Attacking)
		{
			entity->Kill();
		}
	}
	if (dynamic_cast<EntityCorpse*>(entity) != NULL)
	{
		if (Eating)
		{
			if (dynamic_cast<EntityCorpse*>(entity) != NULL)
			{
				float Delta = fmin(((EntityCorpse*)entity)->Energy, EatSpeed) * WorldObj->DeltaTime;
				Energy += Delta;
				((EntityCorpse*)entity)->Energy -= Delta;
			}
		}
	}
}