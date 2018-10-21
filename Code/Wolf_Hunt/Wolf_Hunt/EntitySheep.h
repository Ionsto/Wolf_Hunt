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
		float AgeMate = 40;
		float AgeMax = 80;
		float MateEnergyCost = 30;
		float SheepCost = 10;
		int MateCounter = 0;
		ComponentIDRenderObject IDRenderObjectHead;
		AIBoids BoidsInstance;
		AINeuralNetwork NNInstance;
		std::array<float, 10> NNMemoryArray;
		Vector<float> TargetMovementAcc;
		float TargetRotAcc = 0;
		EntitySheep(World * world);
		virtual ~EntitySheep();
		virtual void Update() override;
		virtual void UpdateAI() override;
		virtual void UpdateRenderObject() override;
		void BoidsAI();
		void RayAI();
		void InitBoidsNetwork();
		void InitRayNetwork();
	};
}

