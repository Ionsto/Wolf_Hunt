#pragma once
#include "EntityLiving.h"
namespace Sim {
	class EntityCorpse :
		public EntityLiving//Ironic
	{
	public:
		float MaxDecayTime = 30;
		float DecayTimer = 0;
		EntityCorpse(World * world);
		virtual ~EntityCorpse();
		virtual void Update() override;
	};
}
