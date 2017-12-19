#include "KeyState.h"



KeyState::KeyState()
{
	Key = Up;
}


KeyState::~KeyState()
{

}
//0 = down, 1 = up
void KeyState::Update()
{
	switch(Key)
	{
	case GoingUp:
		Key = Up;
		break;
	case GoingDown:
		Key = Down;
		break;
	}
}