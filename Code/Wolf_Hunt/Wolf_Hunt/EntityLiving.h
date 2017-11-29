#pragma once
#include "Entity.h"
namespace Sim {
	class EntityLiving : public Sim::Entity
	{
	public:
		float MaxAccelerationForward = 40;
		float MaxAccelerationBack = 20;
		float MaxRotAcceleration = 50;
		float RotAcceleration = 20;
		float TargetRotation = 0;
		Vector<float> TargetAcceleration;
		float AIUpdateTimer = 0;
		float AIUpdateMax = 1;
		//from 0 to 100, 0 means you can't move. 100 is full. 10 is when you start experiecning acc decay
		float Energy = 100;
		float EnergyLossPerAcc = 1;
		enum EntityTypes {
		Wolf,Sheep,Fox,Other
		} Type;
		float Health;
		EntityLiving(Sim::World * wrld);
		~EntityLiving();
		virtual void Update() override;
		virtual void UpdateAI();
		virtual void ApplyWalkForce(Vector<float> Force);
		virtual void Kill() override;
		virtual void UpdateTargets();
	};
};