#pragma once
class GeoObject
{
public:
	GeoObject();
	virtual ~GeoObject();
	virtual void Render() abstract;
};

