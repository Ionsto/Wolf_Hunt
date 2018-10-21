#include "EntitySheep.h"
#include <list>
#include "World.h"
#include "EntityWolf.h"
#include "EntityGrass.h"
#include <algorithm>
#include <array>
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
	//IDRenderObjectHead = wrld->WorldRender.AddCircle(Sim::ComponentRenderCircle(Pos, 5, 1));
	WorldObj->WorldRender.GetCircle(IDRenderObject).Colour = 4;
	//WorldObj->WorldRender.GetCircle(IDRenderObjectHead).Colour = 4;
	InitRayNetwork();
}
void Sim::EntitySheep::InitBoidsNetwork()
{
	NNInstance.Layers.push_back(std::vector<AINode>());
	//Input psedo nodes
	NNInstance.Layers[0].emplace_back(AINode(0));
	NNInstance.Layers[0].emplace_back(AINode(0));
	NNInstance.Layers[0].emplace_back(AINode(0));
	NNInstance.Layers[0].emplace_back(AINode(0));
	NNInstance.Layers[0].emplace_back(AINode(0));
	//Layers[0].push_back(AINode(0));
	for (int l = 0; l < 0; ++l)
	{
		NNInstance.Layers.push_back(std::vector<AINode>());
		for (int n = 0; n < 5; ++n)
		{
			//Hidden
			NNInstance.Layers[l + 1].emplace_back(AINode(NNInstance.Layers[l - 1].size() + 1));
		}
	}

	NNInstance.Layers.push_back(std::vector<AINode>());
	//Output

	//State node psedo one hot softmax
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));
	//Boid nodes	
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));//rep
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));//clump
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));//coehs
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));//flee
	NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));//wall aversion
}
void Sim::EntitySheep::InitRayNetwork()
{
	NNInstance.Layers.push_back(std::vector<AINode>());
	/*
	Inputs:
	[Sampledata [RGB]]
	RotationVelocity
	Velocity[X,Y]
	Energy
	[Memory (10)]
	*/
	auto & firstlayer = NNInstance.Layers.front();
	for (int i = 0; i < (ComponentRenderCamera::SampleCount*4) + 3 + 10; ++i)
	{
		firstlayer.emplace_back(AINode(0));
	}
	static constexpr std::array<int,2> LayerNodeCounts = { 50,20 };
	for (int l = 0; l < LayerNodeCounts.size(); ++l)
	{
		NNInstance.Layers.push_back(std::vector<AINode>());
		for (int n = 0; n < LayerNodeCounts[l]; ++n)
		{
			//Hidden
			NNInstance.Layers[l + 1].emplace_back(AINode(NNInstance.Layers[l].size() + 1));
		}
	}

	NNInstance.Layers.push_back(std::vector<AINode>());
	//Output
	auto & outputlayer = NNInstance.Layers.back();
	/*
	AccX
	AccY
	RotAcc
	softmax{
		Mate
		Eat
		Move
	}
	[Memory 10]
	*/
	for (int i = 0; i < 16; ++i)
	{
		NNInstance.Layers.back().emplace_back(AINode((NNInstance.Layers.end() - 2)->size() + 1));
	}
	//State node psedo one hot softmax
}


Sim::EntitySheep::~EntitySheep()
{
	if (IDRenderObjectHead.Valid)
	{
		//std::cout << "Delete circle from: " << (unsigned int)this << "\n";
		//WorldObj->WorldRender.RemoveCircle(IDRenderObjectHead);
	}
}

void Sim::EntitySheep::Update()
{
	EntityLiving::Update();
	this->ApplyWalkForce(TargetMovementAcc);
	this->ApplyMoment(TargetRotAcc);
	Age += WorldObj->DeltaTime;
	if (Age > AgeMax)
	{
		Kill();
	}
}
void Sim::EntitySheep::UpdateRenderObject()
{
	Entity::UpdateRenderObject();
	//auto & Object = WorldObj->WorldRender.GetCircle(IDRenderObjectHead);
	//Object.Position = Pos + (Vector<float>(cos(Rot),sin(Rot))*10);
}
void Sim::EntitySheep::UpdateAI()
{
	//Do ai updates
	EntityLiving::UpdateAI();
	this->RayAI();
}
void Sim::EntitySheep::BoidsAI()
{
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
	AIState = std::distance(Testarray, std::max_element(Testarray, Testarray + 3));
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
				if (NearEnt->Energy > MateEnergyCost)
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
void Sim::EntitySheep::RayAI()
{
	std::vector<float> Inputs;
	auto & Camera = WorldObj->WorldRender.GetCamera(IDRenderVision);
	int inputiter = 0;
	for (int i = 0; i < Camera.SampleCount;++i)
	{
		Colour col = Colour(Camera.Rays[i]);
		Inputs.push_back(col.R);
		Inputs.push_back(col.G);
		Inputs.push_back(col.B);
		Inputs.push_back(Camera.Rays[i].Distance);
	}
	Inputs.push_back(Health);
	Inputs.push_back(Energy);
	Inputs.push_back(Age);
	Inputs.insert(Inputs.end(), NNMemoryArray.begin(), NNMemoryArray.end());
	NNInstance.Update(Inputs);
	TargetMovementAcc.X = 0;
	TargetMovementAcc.Y = 0;
	TargetMovementAcc.Z = 0;
	TargetMovementAcc += Vector<float>(cos(Rot), sin(Rot)) * NNInstance.Layers.back()[0].Output * MaxAccelerationForward;
	//perp
	TargetMovementAcc += Vector<float>(-sin(Rot), cos(Rot)) * NNInstance.Layers.back()[1].Output * MaxAccelerationForward;
	TargetRotAcc = NNInstance.Layers.back()[2].Output * MaxRotAcceleration;

	int AIState = 0;
	float Testarray[] = { NNInstance.Layers.back()[3].Output,
		NNInstance.Layers.back()[4].Output,
		NNInstance.Layers.back()[5].Output, };
	for (int i = 0; i < NNMemoryArray.size(); ++i)
	{
		NNMemoryArray[i] = NNInstance.Layers.back()[6+i].Output;
	}
	AIState = std::distance(Testarray, std::max_element(Testarray, Testarray + 3)); switch (AIState)
	{
		//Boid
	case 0:
		//already done
		break;
	case 1:
		//Eat
		Energy += AIUpdateMax * 50;
		break;
	case 2:
		//Mate
		if (Energy > MateEnergyCost && Age > AgeMate)
		{
			auto child = std::make_unique<EntitySheep>(WorldObj);
			child->Energy = MateEnergyCost * 2 - SheepCost;
			child->NNInstance.Copy(NNInstance);
			child->NNInstance.Randomise(0.2);
			int id = WorldObj->AddEntity(move(child));
			if (id != -1)
			{
				float angle = (rand() % 620) / 100.0;
				WorldObj->EntityList[id]->SetLocation((this->Pos + Vector<float>(cos(angle), sin(angle)) * (Size+5)));
			}
			Energy -= MateEnergyCost;
		}
		break;
	}
}