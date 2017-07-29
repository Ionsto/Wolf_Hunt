#pragma once
namespace Sim {
	class World;
	class Entity
	{
	public:
		World * WorldObj;
		Entity(World * wrld);
		~Entity();
		virtual void Update();
	};
};