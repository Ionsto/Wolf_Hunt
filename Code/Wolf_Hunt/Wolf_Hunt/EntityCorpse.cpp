#include "EntityCorpse.h"
#include "World.h"
#include <math.h>

Sim::EntityCorpse::EntityCorpse(World * world) : EntityLiving(world)
{
	Type = EntityTypes::Corpse;
	WorldObj->WorldRender.GetCircle(IDRenderObject).Colour = 1;
}


Sim::EntityCorpse::~EntityCorpse()
{
}

void Sim::EntityCorpse::Update()
{
	EntityLiving::Update();
	DecayTimer += WorldObj->DeltaTime;
	Energy -= (100.0/MaxDecayTime) * WorldObj->DeltaTime;
	Energy = fmaxf(Energy, 0);
	if (Energy <= 0)
	{
		Entity::Kill();
	}
}