#include "SPGameInstance.h"



Sim::SPGameInstance::SPGameInstance()
{
	WorldInstance = std::make_unique<World>();
	for (int i = 0; i < 5; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<EntityWolf>(WorldInstance.get()));
		PlayerWolf.push_back((EntityWolf*)WorldInstance->EntityList[id].get());
	}
}


Sim::SPGameInstance::~SPGameInstance()
{
}

void Sim::SPGameInstance::Update()
{

}