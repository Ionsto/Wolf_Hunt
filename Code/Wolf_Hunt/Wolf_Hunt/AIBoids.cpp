#include "AIBoids.h"
#include "EntitySheep.h"
#include "EntityWolf.h"

Sim::AIBoids::AIBoids()
{
	Repulsion = 5;
	Clump = .1;
	Coheasion = 1;
	Flee = .8;
}


Sim::AIBoids::~AIBoids()
{
}

Sim::Vector<float> Sim::AIBoids::CalculateAcc(Entity * Self,std::vector<Entity*> list)
{
	Sim::Vector<float> Result = Vector<float>();
	//Result += CalculateCoheasion(Self,list) * Coheasion;
	//Result += CalculateRepulsion(Self, list) * Repulsion;
	//Result += CalculateClump(Self, list) * Clump;
	Result += CalculateFlee(Self, list) * Flee;
	Result = Result;
	return Result;
}

Sim::Vector<float> Sim::AIBoids::CalculateRepulsion(Entity * Self, std::vector<Entity*> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto ent in list)
	{
		if (dynamic_cast<Sim::EntitySheep*>(ent) != NULL) {
			Vector<float> dist = Self->Pos - ent->Pos;
			Acc += dist *(1 / dist.Dot(dist));
		}
	}
	return Acc;
}
Sim::Vector<float> Sim::AIBoids::CalculateClump(Entity * Self, std::vector<Entity*> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto ent in list)
	{
		if (dynamic_cast<Sim::EntitySheep*>(ent) != NULL) {
			Vector<float> dist = ent->Pos - Self->Pos;
			Acc += dist / sqrt(dist.Dot(dist));
		}
	}
	return Acc;
}
Sim::Vector<float> Sim::AIBoids::CalculateCoheasion(Entity * Self, std::vector<Entity*> list)
{
	Sim::Vector<float> Result = Vector<float>();
	for each (auto ent in list)
	{
		if (dynamic_cast<Sim::EntitySheep*>(ent) != NULL) {
			Vector<float> dist = ent->Pos - Self->Pos;
			Result += (ent->Pos - ent->PosOld) / (dist.Dot(dist));
		}
	}
	Result = Result / list.size();
	return Result;
}

Sim::Vector<float> Sim::AIBoids::CalculateFlee(Entity * Self, std::vector<Entity*> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto ent in list)
	{
		if (dynamic_cast<Sim::EntityWolf*>(ent) != NULL) {
			Vector<float> dist = Self->Pos - ent->Pos;
			Acc += dist *(1 / sqrtf(dist.Dot(dist)));
		}
	}
	return Acc;
}