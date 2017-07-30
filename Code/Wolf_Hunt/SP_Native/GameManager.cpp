#include "GameManager.h"
#include "./../Wolf_Hunt/EntitySheep.h"
#include "./../Wolf_Hunt/EntityWolf.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	WorldInstance = std::make_unique<Sim::World>();
	Window.create(sf::VideoMode(800, 600), "My window");
	RenderEngine = RenderSystem();
	Running = true;
	int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(Sim::EntitySheep(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(30, 30));
	id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(Sim::EntitySheep(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(20, 20));
	id = WorldInstance->AddEntity(std::make_unique<Sim::EntityWolf>(Sim::EntityWolf(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(100, 100));
	Mouse = MouseState();
}
void GameManager::Update()
{
	WorldInstance->Update();
}
void GameManager::Render()
{
	Window.clear();
	RenderEngine.Render(WorldInstance.get(),&Window);
	Window.display();
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
			Running = false;
			break;
		case sf::Event::MouseButtonPressed:
			Mouse.Location.X = event.mouseButton.x;
			Mouse.Location.Y = event.mouseButton.y;
			if (event.mouseButton.button == 0)
			{
				Mouse.UpdateLeft(0);
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.UpdateRight(0);
			}
			break;
		case sf::Event::MouseButtonReleased:
			Mouse.Location.X = event.mouseButton.x;
			Mouse.Location.Y = event.mouseButton.y;
			if (event.mouseButton.button == 0)
			{
				Mouse.UpdateLeft(1);
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.UpdateRight(1);
			}
			break;
			// key pressed
		case sf::Event::KeyPressed:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Update(0);
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Update(1);
			}
			break;
		default:
			break;
		}
	}

	//Gameplay parse

	if (Mouse.Left == ButtonState::GoingDown)
	{
		//Search
	}
}
void GameManager::MainLoop()
{
	while (Running)
	{
		PollInput();
		Update();
		Render();
	}
	Window.close();
}