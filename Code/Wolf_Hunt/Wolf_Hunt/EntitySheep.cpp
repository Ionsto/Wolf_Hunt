#include "EntitySheep.h"
#include <list>
#include "World.h"


Sim::EntitySheep::EntitySheep(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Sheep;
	BoidsInstance = AIBoids();
}


Sim::EntitySheep::~EntitySheep()
{
}

void Sim::EntitySheep::Update()
{
	EntityLiving::Update();
	UpdateAI();
}
void Sim::EntitySheep::UpdateAI()
{
	//Do ai updates
	std::list<Entity*> NearEntity = WorldObj->GetNearbyEntities(GridID);
	NearEntity.remove(this);
	Vector<float> Acc;
	int AIState = 0;
	switch (AIState)
	{
		//Boid
		case 0:
		Acc = BoidsInstance.CalculateAcc(this, NearEntity);
		if (Acc.Dot(Acc) > MaxAcceleration * MaxAcceleration)
		{
			Acc = Acc * (MaxAcceleration / sqrtf(Acc.Dot(Acc)));
		}
		Acceleration += Acc;
			break;
		case 1:
			//Eat
			break;
		case 2:
			//Mate
			break;
	}
	//NearEntity.clear();
}