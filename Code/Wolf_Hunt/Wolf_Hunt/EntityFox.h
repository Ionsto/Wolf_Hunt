#pragma once
#include "EntityLiving.h"
#include "EntityHunter.h"
namespace Sim {
	class EntityFox :
		public EntityHunter
	{
	protected:
		int AIState;
		enum States
		{
			Chase, Eat
		} ;
	public:
		Vector<float> TargetLocation;
		EntityFox(World * world);
		~EntityFox();
		void UpdateAI() override;
		void Update() override;
		virtual void Collision(Entity * ent) override;
	};
}

