#pragma once
namespace SP_Native {
	enum ButtonState {
		GoingDown, Down, GoingUp, Up
	};
	class KeyState
	{
	public:
		ButtonState Key = ButtonState::Up;
		KeyState();
		~KeyState();
		void Update();
	};
}

