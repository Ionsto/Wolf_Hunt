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
	IDRenderVision = wrld->WorldRender.AddCamera(Sim::ComponentRenderCamera());
}


Sim::EntityLiving::~EntityLiving()
{
	if (IDRenderVision.Valid)
	{
		WorldObj->WorldRender.RemoveCamera(IDRenderVision);
	}
}

void Sim::EntityLiving::Update()
{
	UpdateTargets();
	Entity::Update();
	AIUpdateTimer += WorldObj->DeltaTime;
	if (AIUpdateTimer >= AIUpdateMax) {
		UpdateAI();
		AIUpdateTimer = 0;
	}
	Energy = fminf(100, Energy);
	if (Energy < 0)
	{
		Energy = 0;
		Kill();
	}
	//Update camera
	auto & Camera = WorldObj->WorldRender.GetCamera(IDRenderVision);
	Camera.Position = Pos;
	Camera.Rotation = Rot;
}
void Sim::EntityLiving::UpdateAI()
{
	//nullptr
}
void Sim::EntityLiving::SetLocation(Vector<float> pos)
{
	Entity::SetLocation(pos);
	auto & Camera = WorldObj->WorldRender.GetCamera(IDRenderVision);
	Camera.Position = Pos;
	Camera.Rotation = Rot;
}
void Sim::EntityLiving::ApplyWalkForce(Vector<float> Force)
{
	Force.Z = 0;
	//Double sqrt :(
	float DirectionCoheasion = 1;// sqrt(abs(Force.Normalise().DotXY(Vector<float>(cos(Rot), sin(Rot)))));
	float AccelerationDamp = 1;
	if (Energy < 10)
	{
		AccelerationDamp = Energy / 10;
	}
	if (DirectionCoheasion > 0.9)
	{
		if (Force.DotXY(Force) > MaxAccelerationForward*MaxAccelerationForward)
		{
			ApplyForce(Force.Normalise() * MaxAccelerationForward * AccelerationDamp);
			Energy -= MaxAccelerationForward * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
		else
		{
			ApplyForce(Force * AccelerationDamp);
			Energy -= sqrt(Force.DotXY(Force)) * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
	}
	else
	{
		float acclimit = fmaxf(fmaxf(DirectionCoheasion-0.5, 0) * MaxAccelerationForward, MaxAccelerationBack);
		if (Force.DotXY(Force) > acclimit*acclimit)
		{
			ApplyForce(Force.Normalise() * acclimit * AccelerationDamp);
			Energy -= acclimit * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
		else
		{
			ApplyForce(Force * AccelerationDamp);
			Energy -= Force.DotXY(Force) * EnergyLossPerAcc * WorldObj->DeltaTime;
		}
	}
}
void Sim::EntityLiving::Kill() {
	int id = WorldObj->AddEntity(std::make_unique<EntityCorpse>(WorldObj));
	if (id != -1) {
		WorldObj->EntityList[id]->Pos = Pos;
		WorldObj->EntityList[id]->PosOld = PosOld;
		WorldObj->EntityList[id]->Rot = Rot;
		dynamic_cast<EntityCorpse*>(WorldObj->EntityList[id].get())->Energy = Energy + 60;//dank
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