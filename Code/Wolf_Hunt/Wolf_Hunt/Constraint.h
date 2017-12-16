#pragma once
#include "Entity.h"
namespace Sim {
	class Constraint
	{
	public:
		float SpringConstant;
		float Length;
		World * WorldObj;
		Entity * entityA;
		Entity * entityB;
		std::function<void(Entity*)> Callback;
		Constraint();
		Constraint(Entity * a,Entity * b);
		~Constraint();
		void Update();
		void Resolve(float delta);
		void SetEntityB(Entity * e);
		void EntityDied(Entity * entity);
		bool ConnectionExists();
	};
}

