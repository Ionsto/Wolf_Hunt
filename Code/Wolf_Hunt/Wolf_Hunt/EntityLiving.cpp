#include "EntityLiving.h"
#include <math.h>
#include "World.h"
#include "EntityCorpse.h"

Sim::EntityLiving::EntityLiving(Sim::World * wrld) : Sim::Entity(wrld)
{
	Health = 100;
	Type = EntityTypes::Other;
	this->TargetRotation = 0;
	MaxRotAcceleration = 70;
	RotAcceleration = 20;
}


Sim::EntityLiving::~EntityLiving()
{
}

void Sim::EntityLiving::Update()
{
	Entity::Update();
	AIUpdateTimer += WorldObj->DeltaTime;
	if (AIUpdateTimer >= AIUpdateMax) {
		UpdateAI();
		AIUpdateTimer = 0;
	}
	UpdateTargets();
	Energy = fminf(100, fmaxf(0, Energy));
}
void Sim::EntityLiving::UpdateAI()
{
	//NULL
}
void Sim::EntityLiving::ApplyWalkForce(Vector<float> Force)
{
	Force.Z = 0;
	//Double sqrt :(
	float DirectionCoheasion = sqrt(abs(Force.Normalise().Dot(Vector<float>(cos(Rot),sin(Rot)))));
	float AccelerationDamp = 1;
	if (Energy < 10)
	{
		AccelerationDamp = Energy / 10;
	}
	if (DirectionCoheasion > 0.9)
	{
		if (Force.Dot(Force) > MaxAccelerationForward*MaxAccelerationForward)
		{
			ApplyForce(Force.Normalise() * MaxAccelerationForward * AccelerationDamp);
			Energy -= MaxAccelerationForward * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
		else
		{
			ApplyForce(Force * AccelerationDamp);
			Energy -= sqrt(Force.Dot(Force)) * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
	}
	else
	{
		float acclimit = fmaxf(fmaxf(DirectionCoheasion-0.5, 0) * MaxAccelerationForward, MaxAccelerationBack);
		if (Force.Dot(Force) > acclimit*acclimit)
		{
			ApplyForce(Force.Normalise() * acclimit * AccelerationDamp);
			Energy -= acclimit * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
		else
		{
			ApplyForce(Force * AccelerationDamp);
			Energy -= Force.Dot(Force) * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
	}
}
void Sim::EntityLiving::Kill() {
	int id = WorldObj->AddEntity(std::make_unique<EntityCorpse>(EntityCorpse(WorldObj)));
	if (id != -1) {
		WorldObj->EntityList[id]->Pos = Pos;
		WorldObj->EntityList[id]->PosOld = PosOld;
		WorldObj->EntityList[id]->Rot = Rot;
		dynamic_cast<EntityCorpse*>(WorldObj->EntityList[id].get())->Energy = Energy + 10;
	}
	Entity::Kill();
}

void Sim::EntityLiving::UpdateTargets()
{
	if (OnFloor)
	{
		float RotDist = TargetRotation - Rot;
		RotDist = NormaliseAngle(RotDist) * RotAcceleration;
		if (fabsf(RotDist) > 0.01)
		{
			if (fabsf(RotDist) > MaxRotAcceleration)
			{
				ApplyMoment(copysignf(MaxRotAcceleration, RotDist));
			}
			else
			{
				ApplyMoment(RotDist);
			}
		}
		ApplyWalkForce(TargetAcceleration);
	}
}