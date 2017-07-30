#pragma once
enum ButtonState {
GoingDown, Down, GoingUp, Up
};
class KeyState
{
public:
	ButtonState Key;
	KeyState();
	~KeyState();
	//0 = down, 1 = up
	void Update(int state);
};

