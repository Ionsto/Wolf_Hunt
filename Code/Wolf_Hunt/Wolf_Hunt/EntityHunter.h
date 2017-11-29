#pragma once
namespace Sim {
	class EntityHunter
	{
	public:
		float EatSpeed = 100;
		bool Attacking = false;
		bool Eating = false;
		EntityHunter();
		~EntityHunter();
	};
}

