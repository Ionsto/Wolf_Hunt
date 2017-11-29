#pragma once
#include "EntityLiving.h"
#include "AIBoids.h"
#include "AINeuralNetwork.h"
namespace Sim {
	class EntitySheep :
		public EntityLiving
	{
	public:
		float Age = 0;
		float AgeMax = 80;
		float MateEnergyCost = 20;
		int MateCounter = 0;
		AIBoids BoidsInstance;
		AINeuralNetwork NNInstance;
		EntitySheep(World * world);
		~EntitySheep();
		virtual void Update() override;
		virtual void UpdateAI() override;
	};
}

