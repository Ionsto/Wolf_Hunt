#include "Entity.h"
#include "World.h"


Sim::Entity::Entity(World * wrld)
{
	this->WorldObj = wrld;
	LinearDamp = 0.90;
}


Sim::Entity::~Entity()
{
	//clean up
	WorldObj->WorldGrid[GridID.X][GridID.Y].RemoveEntity(this);
}

void Sim::Entity::SetLocation(Vector<float> pos)
{
	Pos = pos;
	PosOld = pos;
	Vector<int> NewGridID = WorldObj->GetGridIDs(Pos);
	if (NewGridID != GridID)
	{
		//Update Grid
		WorldObj->WorldGrid[NewGridID.X][NewGridID.Y].AddEntity(this);
		WorldObj->WorldGrid[GridID.X][GridID.Y].RemoveEntity(this);
		GridID = NewGridID;
	}
}

void Sim::Entity::Update()
{
	Intergrate();
	EnforceBoundry();
}
void Sim::Entity::EnforceBoundry()
{
	if (Pos.X < 0)
	{
		Pos.X = 0;
		PosOld.X = 0;
	}
	if (Pos.Y < 0)
	{
		Pos.Y = 0;
		PosOld.Y = 0;
	}
	if (Pos.X > WorldObj->WorldSize)
	{
		Pos.X = WorldObj->WorldSize;
		PosOld.X = WorldObj->WorldSize;
	}
	if (Pos.Y > WorldObj->WorldSize)
	{
		Pos.Y = WorldObj->WorldSize;
		PosOld.Y = WorldObj->WorldSize;
	}
}
void Sim::Entity::Intergrate()
{
	//Linear intergration
	Vector<float> NewOld = this->Pos;
	Pos += ((Pos - PosOld) * LinearDamp) + (Acceleration * WorldObj->DeltaTime * WorldObj->DeltaTime);
	PosOld = NewOld;
	Acceleration = Vector<float>();
}
void Sim::Entity::Kill()
{
	//Do death stuff
	Alive = false;
}
void Sim::Entity::ApplyForce(Vector<float> force)
{
	this->Acceleration += force / Mass;
}