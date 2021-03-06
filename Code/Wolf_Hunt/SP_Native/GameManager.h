#pragma once
#include <SFML\Graphics.hpp>
#include "KeyState.h"
#include <Array>
#include "..\Wolf_Hunt\World.h"
#include "..\Wolf_Hunt\EntityWolf.h"
#include "./RenderSystem.h"
#include <chrono>
#include "MouseState.h"
namespace SP_Native {
	class GameManager
	{
	public:
		GuiHud GameHud;
		sf::Clock clock;
		std::unique_ptr<RenderSystem> RenderEngine;
		bool Running;
		MouseState Mouse;
		std::array<KeyState, 255> KeyArray;
		sf::RenderWindow Window;
		std::unique_ptr<Sim::World> WorldInstance;
		Sim::EntityWolf * Selected = nullptr;
		std::chrono::steady_clock Clock;
		float TimeDifference = 0;
		GameManager();
		~GameManager();
		void Init();
		void Update();
		void PollInput();
		void Render();
		void MainLoop();
		void DebugObjectSizes();
		void UpdateCamera();
	};
}
