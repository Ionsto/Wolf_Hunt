#include "MouseState.h"



MouseState::MouseState()
{
}


MouseState::~MouseState()
{
}

void MouseState::UpdateLeft(int state)
{
	switch (state)
	{
	case 0:
		switch (Left)
		{
		case Up:
		case GoingUp:
			Left = GoingDown;
			break;
		case GoingDown:
			Left = Down;
		}
		break;
	case 1:
		switch (Left)
		{
		case Down:
		case GoingDown:
			Left = GoingUp;
			break;
		case GoingUp:
			Left = Up;
		}
		break;
	}
}
void MouseState::UpdateRight(int state)
{
	switch (state)
	{
	case 0:
		switch (Right)
		{
		case Up:
		case GoingUp:
			Right = GoingDown;
			break;
		case GoingDown:
			Right = Down;
		}
		break;
	case 1:
		switch (Right)
		{
		case Down:
		case GoingDown:
			Right = GoingUp;
			break;
		case GoingUp:
			Right = Up;
		}
		break;
	}
}