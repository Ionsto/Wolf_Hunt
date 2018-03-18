#pragma once
#include "GeoObject.h"
class GeoTriangle :
	public GeoObject
{
protected:
	float Data[3*2];
public:
	GeoTriangle();
	virtual ~GeoTriangle();
	virtual void Render() override;
};

