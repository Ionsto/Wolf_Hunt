#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "KeyState.h"
#include <Array>
#include "..\Wolf_Hunt\World.h"
#include "..\Wolf_Hunt\EntityWolf.h"
#include "RenderSystem.h"
#include "MouseState.h"
class GameManager
{
public:
	sf::Clock clock;
	RenderSystem RenderEngine;
	bool Running;
	MouseState Mouse;
	std::array<KeyState, 255> KeyArray;
	sf::RenderWindow Window;
	std::unique_ptr<Sim::World> WorldInstance;
	Sim::EntityWolf * Selected = NULL;
	GameManager();
	~GameManager();
	void Init();
	void Update();
	void PollInput();
	void Render();
	void MainLoop();
};

