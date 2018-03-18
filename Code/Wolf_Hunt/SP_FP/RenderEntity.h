#pragma once
#include "./../Wolf_Hunt/Entity.h"
class RenderEntity
{
public:
	RenderEntity();
	virtual ~RenderEntity();
	virtual void Render(Sim::Entity * entity);
};

