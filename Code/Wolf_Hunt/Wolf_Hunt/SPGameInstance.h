#pragma once
#include "GameInstance.h"
#include <memory>
#include "World.h"
#include "EntityWolf.h"
#include <vector>
namespace Sim {
	class SPGameInstance :
		public GameInstance
	{
	public:
		std::vector<EntityWolf*> PlayerWolf;
		std::unique_ptr<World> WorldInstance;
		SPGameInstance();
		~SPGameInstance();
		virtual void Update() override;
	};
}

