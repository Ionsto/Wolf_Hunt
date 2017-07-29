#pragma once
class World;
class Entity
{
public:
	World * WorldObj;
	Entity(World * wrld);
	~Entity();
	virtual void Update();
};

