#pragma once
class GeoObject
{
public:
	GeoObject();
	~GeoObject();
	virtual void* GetData() abstract;
};

