#include "Constraint.h"
#include "World.h"
#include <iostream>


Sim::Constraint::Constraint()
{
	RestitutionConstant = 0.95;
	MaxExpansion = 1;
	entityA = nullptr;
	entityB = nullptr;
	WorldObj = nullptr;
	Callback = std::function<void(Entity*)>(std::bind(&Constraint::EntityDied, this, std::placeholders::_1));
}
Sim::Constraint::Constraint(Entity * a, Entity * b) : Constraint()
{
	entityA = a;
	entityB = b;
	WorldObj = a->WorldObj;
	Vector<float> Diff = entityA->Pos - entityB->Pos;
	Length = sqrt(Diff.DotXY(Diff));
}


Sim::Constraint::~Constraint()
{
}
bool Sim::Constraint::CheckConnectionLength()
{
	Vector<float> Diff = entityA->Pos - entityB->Pos;
	float Distance = sqrt(Diff.DotXY(Diff));
	return Length * (1 + MaxExpansion) > Distance && Length * (1 - MaxExpansion) < Distance;
}
void Sim::Constraint::Update()
{
	if (this->ConnectionExists())
	{
		constexpr int Itter = 100;
		for (int i = 0; i < Itter; ++i)
		{
			Resolve(WorldObj->DeltaTime / Itter);
		}
		if (!this->CheckConnectionLength())
		{
			SetEntityB(nullptr);
		}
	}
}

void Sim::Constraint::Resolve(float Delta)
{
	Vector<float> Diff = entityA->Pos - entityB->Pos;
	Diff.Z = 0;
	float Distance = sqrt(Diff.DotXY(Diff));
	float SumWeight = entityA->Mass + entityB->Mass;
	Distance = (Length - Distance) / Distance;
	//std::cout << (int)entityA <<"\n";
	entityA->Pos += Diff * Delta * RestitutionConstant * Distance * (entityA->Mass / SumWeight);
	entityB->Pos -= Diff * Delta * RestitutionConstant * Distance * (entityB->Mass / SumWeight);
}
void Sim::Constraint::SetEntityB(Entity * ent)
{
	if (entityB != ent)
	{
		if (entityB != nullptr)
		{
			entityB->UnRegisterDeath(&Callback);
		}
		entityB = ent;
		if (ent != nullptr)
		{
			entityB->RegisterDeath(&Callback);
		}
	}
}
void Sim::Constraint::EntityDied(Entity * ent)
{
	std::cout << "Entity died\n";
	if (ent == entityA)
	{
		entityB = nullptr;
	}
	if (ent == entityB)
	{
		SetEntityB(nullptr);
		entityB = nullptr;
	}
}
bool Sim::Constraint::ConnectionExists()
{
	return (this->entityA != nullptr) && (this->entityB != nullptr);
}