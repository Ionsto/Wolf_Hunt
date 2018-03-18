#pragma once
#include "Entity.h"
namespace Sim {
	class Constraint
	{
	public:
		float SpringConstant;
		float Length;
		float MaxExpansion = 0.5;
		float RestitutionConstant = 0.1;
		World * WorldObj;
		Entity * entityA;
		Entity * entityB;
		std::function<void(Entity*)> Callback;
		Constraint();
		Constraint(Entity * a,Entity * b);
		virtual ~Constraint();
		bool CheckConnectionLength();
		void Update();
		void Resolve(float delta);
		void SetEntityB(Entity * e);
		void EntityDied(Entity * entity);
		bool ConnectionExists();
	};
}

