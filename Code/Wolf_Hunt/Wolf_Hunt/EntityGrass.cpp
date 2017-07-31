#include "EntityGrass.h"
#include "World.h"


Sim::EntityGrass::EntityGrass(Sim::World * wrld) : Sim::Entity(wrld)
{
	Size = 5;
}


Sim::EntityGrass::~EntityGrass()
{
}
void Sim::EntityGrass::Update()
{
	if (!Grown)
	{
		GrowthCount += WorldObj->DeltaTime;
		if (GrowthCount >= MaxGrowthCount)
		{
			Grown = true;
			GrowthCount = 0;
		}
	}
}