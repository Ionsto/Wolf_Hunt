#include "KeyState.h"



KeyState::KeyState()
{
	Key = Up;
}


KeyState::~KeyState()
{
}
//0 = down, 1 = up
void KeyState::Update(int state)
{
	switch (state)
	{
	case 0:
		switch (Key)
		{
		case Up:
		case GoingUp:
			Key = GoingDown;
			break;
		case GoingDown:
			Key = Down;
		}
		break;
	case 1:
		switch (Key)
		{
		case Down:
		case GoingDown:
			Key = GoingUp;
			break;
		case GoingUp:
			Key = Up;
		}
		break;
	}
};