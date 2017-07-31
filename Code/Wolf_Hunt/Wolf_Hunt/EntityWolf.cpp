#include "EntityWolf.h"


Sim::EntityWolf::EntityWolf(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Wolf;
	TargetLocation = Pos; 
	Size = 10;
	MaxAcceleration = 500;
}


Sim::EntityWolf::~EntityWolf()
{

}

void Sim::EntityWolf::Update()
{
	EntityLiving::Update();
	UpdateAI();
}
void Sim::EntityWolf::UpdateAI()
{
	//Do ai updates
	Vector<float> Diff = TargetLocation - Pos;
	if (Diff.Dot(Diff) > MaxAcceleration)
	{
		ApplyForce(Diff.Normalise() * MaxAcceleration);
	}
	else
	{
		ApplyForce(Diff);
	}
}

void Sim::EntityWolf::SetLocation(Vector<float> pos)
{
	Entity::SetLocation(pos);
	TargetLocation = pos;
}