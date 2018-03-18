#pragma once
#include "./../Wolf_Hunt/Vector.h"
struct Intersection{
	bool Intersected;
	float Distance;
	int Colour;
	Intersection(bool inter,float dist,int colour):Intersected(inter)
	,Distance(dist),Colour(colour){};
};
class RenderRay{
public:
    Sim::Vector<float> Pos;
	Sim::Vector<float> Direction;
    float MaxDistance = 30;
    float Distance = 0;
    int Colour = 0;
    RenderRay(){};
    RenderRay(Sim::Vector<float> pos, Sim::Vector<float> dir,float max):Pos(pos),Direction(dir)
    {
    };
};
