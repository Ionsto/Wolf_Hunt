#include "AIBoids.h"
#include "EntitySheep.h"
#include "EntityWolf.h"
#include "World.h"

Sim::AIBoids::AIBoids()
{
	Repulsion = 1000;
	Clump = 6;
	Coheasion = 500;
	Flee = 1500;
	WallAversion = 100;
}


Sim::AIBoids::~AIBoids()
{
}

Sim::Vector<float> Sim::AIBoids::CalculateAcc(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list)
{
	Sim::Vector<float> Result = Vector<float>();
	Result += CalculateCoheasion(Self,list) * Coheasion;
	Result += CalculateRepulsion(Self, list) * Repulsion;
	Result += CalculateClump(Self, list) * Clump;
	Result += CalculateFlee(Self, list) * Flee;
	Result += CalculateWallAversion(Self) * WallAversion;
	//Result = Result;
	return Result;
}

Sim::Vector<float> Sim::AIBoids::CalculateRepulsion(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto entlist in list)
	{
		for each (auto ent in entlist.get())
		{
			if (ent == Self) {continue;}
			if (dynamic_cast<Sim::EntitySheep*>(ent) != nullptr) {
				Vector<float> dist = Self->Pos - ent->Pos;
				Acc += dist *(1 / dist.Dot(dist));
			}
		}
	}
	return Acc;
}
Sim::Vector<float> Sim::AIBoids::CalculateClump(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto entlist in list)
	{
		for each (auto ent in entlist.get())
		{
			if (ent == Self) { continue; }
			if (dynamic_cast<Sim::EntitySheep*>(ent) != nullptr) {
				Vector<float> dist = ent->Pos - Self->Pos;
				Acc += dist / sqrt(dist.Dot(dist));
			}
		}
	}
	return Acc;
}
Sim::Vector<float> Sim::AIBoids::CalculateCoheasion(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list)
{
	Sim::Vector<float> Result = Vector<float>();
	for each (auto entlist in list)
	{
		for each (auto ent in entlist.get())
		{
			if (ent == Self) { continue; }
			if (dynamic_cast<Sim::EntitySheep*>(ent) != nullptr) {
				Vector<float> dist = ent->Pos - Self->Pos;
				Result += (ent->Pos - ent->PosOld) / sqrt(dist.Dot(dist));
			}
		}
	}
	Result = Result / list.size();
	return Result;
}

Sim::Vector<float> Sim::AIBoids::CalculateFlee(Entity * Self, std::vector<std::reference_wrapper<std::vector<Sim::Entity *>>> list)
{
	Vector<float> Acc = Vector<float>();
	for each (auto entlist in list)
	{
		for each (auto ent in entlist.get())
		{
			if (ent == Self) { continue; }
			if (dynamic_cast<EntityHunter*>(ent) != nullptr) {
				Vector<float> dist = Self->Pos - ent->Pos;
				Acc += dist / sqrtf(dist.Dot(dist));
			}
		}
	}
	return Acc;
}
Sim::Vector<float> Sim::AIBoids::CalculateWallAversion(Entity * Self)
{
	Vector<float> Acc = Vector<float>();
	float HalfDist = (Self->WorldObj->WorldSize / 2);
	Acc.X = (HalfDist - Self->Pos.X) / HalfDist;
	Acc.Y = (HalfDist - Self->Pos.Y) / HalfDist;
	Acc.X *= abs(Acc.X);
	Acc.Y *= abs(Acc.Y);
	return Acc;
}