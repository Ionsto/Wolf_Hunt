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
	Window.create(sf::VideoMode(1000, 1000), "My window");
	RenderEngine = RenderSystem();
	Running = true;
	int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(Sim::EntitySheep(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(30, 30));
	id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(Sim::EntitySheep(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(20, 20));
	id = WorldInstance->AddEntity(std::make_unique<Sim::EntityWolf>(Sim::EntityWolf(WorldInstance.get())));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(100, 100));

	for (int i = 0; i < 100; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(Sim::EntitySheep(WorldInstance.get())));
		WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(rand() % WorldInstance->WorldSize, rand() % WorldInstance->WorldSize));
	}
	Mouse = MouseState();
	Window.setKeyRepeatEnabled(false);
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
	Mouse.Update();
	for each(auto keyset in KeyArray)
	{
		keyset.Update();
	}
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
				Mouse.Left = ButtonState::GoingDown;
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.Right = ButtonState::GoingDown;
			}
			break;
		case sf::Event::MouseMoved:
			Mouse.Location.X = event.mouseMove.x;
			Mouse.Location.Y = event.mouseMove.y;
			break;
		case sf::Event::MouseButtonReleased:
			Mouse.Location.X = event.mouseButton.x;
			Mouse.Location.Y = event.mouseButton.y;
			if (event.mouseButton.button == 0)
			{
				Mouse.Left = ButtonState::GoingUp;
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.Right = ButtonState::GoingUp;
			}
			break;
			// key pressed
		case sf::Event::KeyPressed:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Key = ButtonState::GoingDown;
				//std::cout << "KeyDown" << std::endl;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Key = ButtonState::GoingUp;
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
		Selected = NULL;
		for (int i = 0; i < WorldInstance->EntityCount; ++i)
		{
			if (WorldInstance->EntityList[i])
			{
				if (WorldInstance->EntityList[i]->Alive)
				{
					if (dynamic_cast<Sim::EntityWolf*>(WorldInstance->EntityList[i].get()) != NULL)
					{
						Sim::Vector<float> Diff = WorldInstance->EntityList[i]->Pos - Mouse.Location;
						float Distdot = Diff.Dot(Diff);
						if (Distdot < 10 * 10)
						{
							//Select
							Selected = dynamic_cast<Sim::EntityWolf*>(WorldInstance->EntityList[i].get());
						}
					}
				}
			}
		}
	}

	if (Mouse.Right == ButtonState::GoingDown)
	{
		if (Selected != NULL)
		{
			Selected->TargetLocation = Mouse.Location;
		}
	}
	float CameraSpeed = 100;
	if (KeyArray[sf::Keyboard::A].Key == ButtonState::Down)
	{
		RenderEngine.CameraLocation.X += CameraSpeed * WorldInstance->DeltaTime;
	}
	if (KeyArray[sf::Keyboard::D].Key == ButtonState::Down)
	{
		RenderEngine.CameraLocation.X -= CameraSpeed * WorldInstance->DeltaTime;
	}
}
void GameManager::MainLoop()
{
	WorldInstance->DeltaTime = 0.000001;
	sf::Time elapsed = clock.restart();
	while (Running)
	{
		PollInput();
		Update();
		Render();
		sf::Time elapsed = clock.restart();
		WorldInstance->DeltaTime = elapsed.asSeconds();
	}
	Window.close();
}