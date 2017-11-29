#pragma once
#include "EntityLiving.h"
namespace Sim {
	class EntityCorpse :
		public EntityLiving//Ironic
	{
	public:
		float MaxDecayTime = 1000;
		float DecayTimer = 0;
		EntityCorpse(World * world);
		~EntityCorpse();
		virtual void Update() override;
	};
}
