#pragma once
#include "EntityLiving.h"
#include "EntityHunter.h"
#include "Constraint.h"
namespace Sim {
	class EntityWolf :
		public EntityLiving,
		public EntityHunter
	{
	public:
		float LeapCooldown = 5;
		float LeapCooldownTimer = 0;
		//How long a bite is
		float BiteTime = 0.2;
		//Time between starts of bites
		float BiteCooldown = 1;
		float BiterCooldownTimer = 0;
		float LeapPower = 2000;
		float LeapPowerVertical = 2000;
		bool Leaping = false;
		bool Grabbing = false;
		Constraint BiteConstraint;
		Vector<float> TargetLocation;
		EntityWolf(World * world);
		~EntityWolf();
		virtual void Update() override;
		virtual void UpdateAI() override;
		virtual void SetLocation(Vector<float> Pos) override;
		void UseLeap();
		void UseBite();
		void UseGrab();
		virtual void Collision(Entity * ent) override;
	};
}

