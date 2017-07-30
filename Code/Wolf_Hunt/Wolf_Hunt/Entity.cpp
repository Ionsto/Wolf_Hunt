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
	Pos += ((Pos - PosOld) * LinearDamp) + (Acceleration * 0.5);
	PosOld = NewOld;
	Acceleration = Vector<float>();
}
void Sim::Entity::Kill()
{
	//Do death stuff
	Alive = false;
}