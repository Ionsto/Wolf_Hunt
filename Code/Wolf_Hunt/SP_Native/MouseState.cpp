#include "MouseState.h"



MouseState::MouseState()
{
}


MouseState::~MouseState()
{
}

void MouseState::Update()
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