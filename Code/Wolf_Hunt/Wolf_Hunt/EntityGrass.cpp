#include "EntityGrass.h"



Sim::EntityGrass::EntityGrass(Sim::World * wrld) : Sim::Entity(wrld)
{
}


Sim::EntityGrass::~EntityGrass()
{
}
void Sim::EntityGrass::Update()
{
	if (!Grown)
	{
		if (++GrowthCount == MaxGrowthCount)
		{
			Grown = true;
			GrowthCount = 0;
		}
	}
}