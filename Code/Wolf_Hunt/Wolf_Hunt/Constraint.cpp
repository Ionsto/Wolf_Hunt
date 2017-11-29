#include "Constraint.h"
#include "World.h"


Sim::Constraint::Constraint()
{
	entityA = NULL;
	entityB = NULL;
	WorldObj = NULL;
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
	int Itter = 10;
	for (int i = 0; i < Itter; ++i)
	{
		Resolve(WorldObj->DeltaTime / Itter);
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