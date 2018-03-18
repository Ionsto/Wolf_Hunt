#include "KeyState.h"



SP_Native::KeyState::KeyState()
{
	Key = Up;
}


SP_Native::KeyState::~KeyState()
{

}
//0 = down, 1 = up
void SP_Native::KeyState::Update()
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