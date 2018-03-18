#pragma once
#include "Entity.h"
namespace Sim {
	class EntityLiving : public Sim::Entity
	{
	protected:
		float MaxAccelerationForward = 40;
		float MaxAccelerationBack = 20;
		float MaxRotAcceleration = 50;
		float RotAcceleration = 20;
		float TargetRotation = 0;
	public:
		ComponentIDAI IDAI;
		ComponentIDRenderCamera IDRenderVision;
		Vector<float> TargetAcceleration;
		float AIUpdateTimer = 0;
		float AIUpdateMax = 5;
		//from 0 to 100, 0 means you can't move. 100 is full. 10 is when you start experiecning acc decay
		float Energy = 100;
		float EnergyLossPerAcc = 1;
		float Health;
		EntityLiving(Sim::World * wrld);
		virtual ~EntityLiving();
		virtual void Update() override;
		virtual void UpdateAI();
		virtual void ApplyWalkForce(Vector<float> Force);
		virtual void Kill() override;
		virtual void UpdateTargets();
		void SetLocation(Vector<float> pos) override;
	};
};