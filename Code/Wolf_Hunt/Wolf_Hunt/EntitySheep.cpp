#include "EntitySheep.h"
#include <list>
#include "World.h"


Sim::EntitySheep::EntitySheep(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Sheep;
	BoidsInstance = AIBoids();
	Size = 10;
	MaxAcceleration = 200;
}


Sim::EntitySheep::~EntitySheep()
{
}

void Sim::EntitySheep::Update()
{
	UpdateAI();
	EntityLiving::Update();
}
void Sim::EntitySheep::UpdateAI()
{
	//Do ai updates
	std::vector<Entity*> NearEntity = WorldObj->GetNearbyEntities(GridID);
	auto it = std::find(NearEntity.begin(), NearEntity.end(), this);
	std::swap(*it, NearEntity.back());
	NearEntity.pop_back();
	Vector<float> Acc;
	int AIState = 0;
	switch (AIState)
	{
		//Boid
		case 0:
			Acc = BoidsInstance.CalculateAcc(this, NearEntity);
			if (Acc.Dot(Acc) > MaxAcceleration * MaxAcceleration)
			{
				Acc = Acc.Normalise() * MaxAcceleration;
			}
			ApplyForce(Acc);
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