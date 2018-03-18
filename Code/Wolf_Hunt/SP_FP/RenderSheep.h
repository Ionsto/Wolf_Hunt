#pragma once
#include "RenderEntity.h"
#include "GeoBox.h"
#include "GeoTriangle.h"
class RenderSheep :
	public RenderEntity
{
private:
	GeoTriangle Body;
public:
	RenderSheep();
	~RenderSheep();
	virtual void Render(Sim::Entity * entity) override;
};

