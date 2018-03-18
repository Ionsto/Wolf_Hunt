#include "EntitySheep.h"
#include <list>
#include "World.h"
#include "EntityWolf.h"
#include "EntityGrass.h"
#include <algorithm>
#include <iterator>

Sim::EntitySheep::EntitySheep(Sim::World * wrld) : Sim::EntityLiving(wrld)
{
	Type = EntityTypes::Sheep;
	BoidsInstance = AIBoids();
	NNInstance = AINeuralNetwork();
	MaxAccelerationForward = 500;
	MaxAccelerationBack = 100;
	MaxRotAcceleration = 50;
	RotAcceleration = 15;
	//RND AI update speeds to not cause stutter en mass
	AIUpdateMax *= (rand() % 100)/100.0;
	EnergyLossPerAcc = 2 / 500.0;
	WorldObj->WorldRender.GetCircle(IDRenderObject).Colour = 4;
}


Sim::EntitySheep::~EntitySheep()
{
}

void Sim::EntitySheep::Update()
{
	EntityLiving::Update();
	Age += WorldObj->DeltaTime;
	if (Age > AgeMax)
	{
		Kill();
	}
}
void Sim::EntitySheep::UpdateAI()
{
	//Do ai updates
	EntityLiving::UpdateAI();
	auto NearEntity = WorldObj->GetNearbyEntities(GridID);
	Vector<float> Acc;
	int AIState = 0;
	//Update NN
	std::vector<float> Inputs;
	//Sheepcount/wolfcount/grown grass count
	int SheepCount = 0, WolfCount = 0, GrassCount = 0;
	for (auto & entitylist : NearEntity)
	{
		for (auto & entity : entitylist.get())
		{
			if (entity != this)
			{
				if (entity->Type == EntityTypes::Wolf || EntityTypes::Fox)
				{
					++WolfCount;
				}
				if (entity->Type == EntityTypes::Sheep)
				{
					++SheepCount;
				}
			}
		}
	}
	Inputs.push_back(WolfCount);
	Inputs.push_back(SheepCount);
	Inputs.push_back(GrassCount);
	Inputs.push_back(Health);
	Inputs.push_back(Energy);
	//Inputs.push_back((float)(MateCounter/15));
	NNInstance.Update(Inputs);
	//Push back AI states
	float Testarray[] = { NNInstance.Layers.back()[0].Output, 
		NNInstance.Layers.back()[1].Output,
		NNInstance.Layers.back()[2].Output, };
	AIState = std::distance(Testarray,std::max_element(Testarray, Testarray + 3));
	//Boid nodes	
	BoidsInstance.Repulsion = NNInstance.Layers.back()[3].Output;//rep
	BoidsInstance.Clump = NNInstance.Layers.back()[4].Output;//clump
	BoidsInstance.Coheasion = NNInstance.Layers.back()[5].Output;//coehs
	BoidsInstance.Flee = NNInstance.Layers.back()[6].Output;//flee
	BoidsInstance.WallAversion = NNInstance.Layers.back()[7].Output;//wall aversion
	//Update boids
	switch (AIState)
	{
		//Boid
		case 0:
			Acc = BoidsInstance.CalculateAcc(this, NearEntity);
			TargetRotation = atan2f(Acc.Y, Acc.X);
			TargetAcceleration = Acc;
			break;
		case 1:
			//Eat
			Energy += AIUpdateMax * 50;
			break;
		case 2:
			//Mate
			if (Energy > MateEnergyCost)
			{
				auto NearEnt = dynamic_cast<EntitySheep*>(WorldObj->GetClosestEntity(this));
				//Check if you are a sheep
				if (NearEnt != nullptr)
				{
					if (Energy > MateEnergyCost)
					{
						//Splice the genes
						Vector<float> diff = this->Pos - NearEnt->Pos;
						float MinDistance = ((Size * 2)*(Size * 2)) + 10;
						if (diff.DotXY(diff) < MinDistance)
						{
							auto child = std::make_unique<EntitySheep>(WorldObj);
							child->Energy = MateEnergyCost * 2 - SheepCost;
							int id = WorldObj->AddEntity(move(child));
							if (id != -1)
							{
								WorldObj->EntityList[id]->SetLocation((this->Pos + NearEnt->Pos) * 0.5);
							}
						}
						Energy -= MateEnergyCost;
						NearEnt->Energy -= MateEnergyCost;
					}
				}
			}
			break;
	}
	if (AIState != 2)
	{
		//MateCounter = 0;
	}
}