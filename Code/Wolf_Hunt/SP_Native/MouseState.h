#pragma once
#include "KeyState.h"
#include ".\..\Wolf_Hunt\Vector.h"
class MouseState
{
public:
	ButtonState Left;
	ButtonState Right;
	Sim::Vector<float> Location;
	MouseState();
	~MouseState();
	void Update();
};

