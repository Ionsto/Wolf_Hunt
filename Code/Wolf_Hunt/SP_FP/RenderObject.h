#pragma once
#include "./../Wolf_Hunt/Vector.h"
#include "RenderRay.h"
class RenderObject{
public:
    Sim::Vector<float> Pos;
    int Colour;
    virtual Intersection GetRayIntersection(RenderRay & ray)
    {
        return Intersection(false,0,0);
    };
};
