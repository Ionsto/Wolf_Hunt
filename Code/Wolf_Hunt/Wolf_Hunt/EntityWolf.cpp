#include "EntityWolf.h"


Sim::EntityWolf::EntityWolf(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Wolf;
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
}