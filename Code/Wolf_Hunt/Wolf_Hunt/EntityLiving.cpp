#include "EntityLiving.h"
#include <math.h>


Sim::EntityLiving::EntityLiving(Sim::World * wrld) : Sim::Entity(wrld)
{
	Health = 100;
	Type = EntityTypes::Other;
}


Sim::EntityLiving::~EntityLiving()
{
}

void Sim::EntityLiving::Update()
{
	if (Acceleration.Dot(Acceleration) > MaxAcceleration * MaxAcceleration)
	{
		Acceleration = Acceleration * (MaxAcceleration / sqrtf(Acceleration.Dot(Acceleration)));
	}
	Entity::Update();
	if (Acceleration.Dot(Acceleration) > MaxAcceleration * MaxAcceleration)
	{
		Acceleration = Acceleration * (MaxAcceleration / sqrtf(Acceleration.Dot(Acceleration)));
	}
}
void Sim::EntityLiving::UpdateAI()
{
	//NULL
}