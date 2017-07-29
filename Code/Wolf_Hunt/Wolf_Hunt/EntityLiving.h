#pragma once
#include "Entity.h"
class EntityLiving : public Entity
{
public:
	float Health;
	bool Alive;
	EntityLiving(World * wrld);
	~EntityLiving();
	virtual void Update() override;
	virtual void UpdateAI();
};

