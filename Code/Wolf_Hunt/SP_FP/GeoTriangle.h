#pragma once
#include "GeoObject.h"
class GeoTriangle :
	public GeoObject
{
public:
	float Data[3*2];
	GeoTriangle();
	~GeoTriangle();
	virtual void* GetData() override;
};

