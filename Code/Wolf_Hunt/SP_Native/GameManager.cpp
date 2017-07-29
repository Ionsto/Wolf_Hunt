#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	WorldInstance = std::make_unique<Sim::World>();

}
void GameManager::Update()
{

}
void GameManager::Render()
{

}
void GameManager::PollInput()
{

	sf::Event event;

	// while there are pending events...
	while (Window.pollEvent(event))
	{
		// check the type of the event...
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			Window.close();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			this->KeyState[event.key.code].Update(0);
			break;
		case sf::Event::KeyReleased:
			this->KeyState[event.key.code].Update(1);
			break;
		default:
			break;
		}
	}
}
void GameManager::MainLoop()
{
	
}