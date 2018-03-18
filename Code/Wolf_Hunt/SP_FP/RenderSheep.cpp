#include "RenderSheep.h"



RenderSheep::RenderSheep()
{
	Body = GeoTriangle();
}


RenderSheep::~RenderSheep()
{
}

void RenderSheep::Render(Sim::Entity * ent)
{
	Body.Render();
}