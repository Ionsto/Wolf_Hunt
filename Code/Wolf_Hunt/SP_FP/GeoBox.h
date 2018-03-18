#pragma once
#include "GeoObject.h"
class GeoBox : public GeoObject
{
public:
	GeoBox();
	virtual ~GeoBox();
	virtual void Render() override;
};

