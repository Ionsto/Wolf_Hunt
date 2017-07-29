#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "..\Wolf_Hunt\World.h"
enum ButtonState {
	GoingDown, Down, GoingUp, Up
};
struct KeyState {
	ButtonState Key;
	KeyState()
	{
		Key = Up;
	}
	//0 = down, 1 = up
	void Update(int state)
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
	}
};
class GameManager
{
public:
	ButtonState MouseState;
	std::array<KeyState, 255> KeyState;
	sf::RenderWindow Window;
	std::unique_ptr<Sim::World> WorldInstance;
	GameManager();
	~GameManager();
	void Init();
	void Update();
	void PollInput();
	void Render();
	void MainLoop();
};

