#include "EntityWolf.h"


Sim::EntityWolf::EntityWolf(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Wolf;
	TargetLocation = Pos;
}


Sim::EntityWolf::~EntityWolf()
{

}

void Sim::EntityWolf::Update()
{
	EntityLiving::Update();
}
void Sim::EntityWolf::UpdateAI()
{
	//Do ai updates
	Vector<float> Diff = TargetLocation - Pos;
	this->Acceleration += Diff.Normalise() * MaxAcceleration;
}

void Sim::EntityWolf::SetLocation(Vector<float> pos)
{
	Entity::SetLocation(pos);
	TargetLocation = pos;
}