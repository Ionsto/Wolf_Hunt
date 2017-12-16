#include "Constraint.h"
#include "World.h"


Sim::Constraint::Constraint()
{
	entityA = nullptr;
	entityB = nullptr;
	WorldObj = nullptr;
	Callback = std::function<void(Entity*)>(std::bind(&Constraint::EntityDied, this, std::placeholders::_1));
}
Sim::Constraint::Constraint(Entity * a, Entity * b)
{
	entityA = a;
	entityB = b;
	WorldObj = a->WorldObj;
	Vector<float> Diff = entityA->Pos - entityB->Pos;
	Length = sqrt(Diff.Dot(Diff));
}


Sim::Constraint::~Constraint()
{
}

void Sim::Constraint::Update()
{
	if (this->ConnectionExists())
	{
		int Itter = 10;
		for (int i = 0; i < Itter; ++i)
		{
			Resolve(WorldObj->DeltaTime / Itter);
		}
	}
}

void Sim::Constraint::Resolve(float Delta)
{
	Vector<float> Diff = entityA->Pos - entityB->Pos;
	float Distance = sqrt(Diff.Dot(Diff));
	float SumWeight = entityA->Mass + entityB->Mass;
	Distance = (Length - Distance) / Distance;
	entityA->Pos += Diff * Distance * (entityA->Mass / SumWeight);
	entityB->Pos -= Diff * Distance * (entityB->Mass / SumWeight);
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
	if (ent == entityA)
	{
		entityB = nullptr;
	}
	if (ent == entityB)
	{
		entityB = nullptr;
	}
}
bool Sim::Constraint::ConnectionExists()
{
	return (this->entityA != nullptr) && (this->entityB != nullptr);
}