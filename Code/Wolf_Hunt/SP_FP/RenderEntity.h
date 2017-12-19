#pragma once
#include "./../Wolf_Hunt/Entity.h"
class RenderEntity
{
public:
	RenderEntity();
	~RenderEntity();
	void Render(Sim::Entity * entity);
};

