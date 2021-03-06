#include "EntityWolf.h"
#include "EntitySheep.h"
#include "EntityCorpse.h"
#include "World.h"
#include <iostream>

Sim::EntityWolf::EntityWolf(Sim::World * wrld) : Sim::EntityHunter(wrld)
{
	Type = EntityTypes::Wolf;
	TargetLocation = Vector<float>(-1,-1); 
	MaxAccelerationForward = 500;
	MaxAccelerationBack = 200;
	LeapPower = 7000;
	LeapPowerVertical = 400;
	EnergyLossPerAcc = 2 / 500.0;
	HoldConstraint->entityA = this;
	EatingConstraint->entityA = this;
	std::cout << (int)this << "\n";
	WorldObj->WorldRender.GetCircle(IDRenderObject).Colour = 5;
}


Sim::EntityWolf::~EntityWolf()
{

}

void Sim::EntityWolf::Update()
{
	EntityHunter::Update();
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
			if (Diff.DotXY(Diff) > CloseDistSqrd)
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
}
void Sim::EntityWolf::UpdateAI()
{
	EntityHunter::UpdateAI();
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
		Energy -= sqrt(force.DotXY(force)) * EnergyLossPerAcc;
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

	std::cout << "Eat" << std::endl;
	if (!EatingConstraint->ConnectionExists())
	{
		std::cout << "Try eat" << std::endl;
		auto EntityClosest = WorldObj->GetClosestEntity(this);
		if (dynamic_cast<EntityCorpse*>(EntityClosest) != nullptr)
		{
			std::cout << "Neighbor found" << std::endl;
			TryEat(EntityClosest);
		}
	}
	else
	{
		EatingConstraint->SetEntityB(nullptr);
	}
	
}
void Sim::EntityWolf::UseGrab()
{

	std::cout << "Grab" << std::endl;
	if (!HoldConstraint->ConnectionExists())
	{
		std::cout << "Try grab" << std::endl;
		auto EntityClosest = WorldObj->GetClosestEntity(this);
		if (EntityClosest != nullptr)
		{
			std::cout << "Neighbor found" << std::endl;
			TryHold(EntityClosest);
		}
	}
	else
	{
		HoldConstraint->SetEntityB(nullptr);
	}
}

void Sim::EntityWolf::Collision(Entity * entity)
{
	
	
	if (dynamic_cast<EntitySheep*>(entity) != nullptr)
	{
		if (Attacking)
		{
			entity->Alive = false;
		}
	}
}