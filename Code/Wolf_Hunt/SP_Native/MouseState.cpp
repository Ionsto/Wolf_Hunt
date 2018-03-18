#include "MouseState.h"



SP_Native::MouseState::MouseState()
{
}


SP_Native::MouseState::~MouseState()
{
}

void SP_Native::MouseState::Update()
{
	switch (Left)
	{
	case GoingUp:
		Left = Up;
		break;
	case GoingDown:
		Left = Down;
		break;
	}
	switch (Right)
	{
	case GoingUp:
		Right = Up;
		break;
	case GoingDown:
		Right = Down;
		break;
	}
}