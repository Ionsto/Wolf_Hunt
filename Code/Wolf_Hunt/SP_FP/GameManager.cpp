#include "GameManager.h"
#include "./../Wolf_Hunt/EntitySheep.h"
#include "./../Wolf_Hunt/EntityWolf.h"
#include "./../Wolf_Hunt/EntityFox.h"
#include <iostream>

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	WorldInstance = std::make_unique<Sim::World>();
	Window.create(sf::VideoMode(800, 800), "My window");
	//Window.create(sf::VideoMode::getFullscreenModes()[0], "Wolf hunt SP", sf::Style::Fullscreen);
	RenderEngine = std::make_unique<RenderSystem>(&Window);

	Running = true;
	//int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(WorldInstance.get()));
	//WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(30, 30));
	//id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(WorldInstance.get()));
	//WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(20, 20));
	int id = WorldInstance->AddEntity(std::make_unique<Sim::EntityWolf>(WorldInstance.get()));
	WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(100, 100));
	/*for (int i = 0; i < 1500; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(WorldInstance.get()));
		WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(rand() % WorldInstance->WorldSize, rand() % WorldInstance->WorldSize));
		((Sim::EntitySheep*)WorldInstance->EntityList[id].get())->NNInstance.Randomise(100);
		((Sim::EntitySheep*)WorldInstance->EntityList[id].get())->Age += rand() % 40;
	}
	for (int i = 0; i < 10; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<Sim::EntityFox>(Sim::EntityFox(WorldInstance.get())));
		WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(rand() % WorldInstance->WorldSize, rand() % WorldInstance->WorldSize));
	}*/
	Mouse = MouseState();
	Window.setKeyRepeatEnabled(false);
	std::cout << "Init complete" << std::endl;
	GameHud = GuiHud(this);
}
void GameManager::Update()
{
	UpdateCamera();
	WorldInstance->Update();
	GameHud.Update();
}
void GameManager::Render()
{
	Window.clear();
	RenderEngine->Render(WorldInstance.get());
	RenderEngine->Render(WorldInstance.get());
	RenderEngine->Render(WorldInstance.get());
	GameHud.Render(&Window);
	Window.display();
}
void GameManager::PollInput()
{

	sf::Event event;

	// while there are pending events...
	Mouse.Update();
	for(int i = 0; i < KeyArray.size();++i)
	{
		KeyArray[i].Update();
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
		Selected = nullptr;
		for (int i = 0; i < WorldInstance->EntityCount; ++i)
		{
			if (WorldInstance->EntityList[i])
			{
				if (WorldInstance->EntityList[i]->Alive)
				{
					{
						auto selected = dynamic_cast<Sim::EntityLiving*>(WorldInstance->EntityList[i].get());
						if (selected != nullptr)
						{
							Sim::Vector<float> Diff = WorldInstance->EntityList[i]->Pos - (RenderEngine->CameraLocation + Mouse.Location);
							float Distdot = Diff.DotXY(Diff);
							if (Distdot < 10 * 10)
							{
								//Debug infomation
								std::cout << "Type:" << selected->Type << std::endl;
								std::cout << "Health:" << selected->Health << std::endl;
								std::cout << "Energy:" << selected->Energy << std::endl;
								std::cout << "Pointer:" << (int)selected << std::endl;
							}
						}
					}
					if (dynamic_cast<Sim::EntityWolf*>(WorldInstance->EntityList[i].get()) != nullptr)
					{
						Sim::Vector<float> Diff = WorldInstance->EntityList[i]->Pos - (RenderEngine->CameraLocation + Mouse.Location);
						float Distdot = Diff.DotXY(Diff);
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
		if (Selected != nullptr)
		{
			Selected->TargetLocation = Mouse.Location + RenderEngine->CameraLocation;
		}
	}
	if (KeyArray[sf::Keyboard::Space].Key == ButtonState::GoingDown)
	{
		if (Selected != nullptr)
		{
			Selected->UseLeap();
		}
	}
	if (KeyArray[sf::Keyboard::E].Key == ButtonState::GoingDown)
	{
		if (Selected != nullptr)
		{
			Selected->UseBite();
		}
	}
	if (KeyArray[sf::Keyboard::Q].Key == ButtonState::GoingDown)
	{
		if (Selected != nullptr)
		{
			Selected->UseGrab();
		}
	}
}
void GameManager::UpdateCamera()
{
	float CameraSpeed = 500;
	if (KeyArray[sf::Keyboard::Escape].Key == ButtonState::GoingDown)
	{
		Running = false;
	}
	if (KeyArray[sf::Keyboard::Escape].Key == ButtonState::GoingDown)
	{
		Running = false;
	}
	if (KeyArray[sf::Keyboard::A].Key == ButtonState::Down || KeyArray[sf::Keyboard::A].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.X -= CameraSpeed * WorldInstance->DeltaTime;
	}
	if (KeyArray[sf::Keyboard::D].Key == ButtonState::Down || KeyArray[sf::Keyboard::D].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.X += CameraSpeed * WorldInstance->DeltaTime;
	}
	if (KeyArray[sf::Keyboard::W].Key == ButtonState::Down || KeyArray[sf::Keyboard::W].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.Y -= CameraSpeed * WorldInstance->DeltaTime;
	}
	if (KeyArray[sf::Keyboard::S].Key == ButtonState::Down || KeyArray[sf::Keyboard::S].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.Y += CameraSpeed * WorldInstance->DeltaTime;
	}
	if (RenderEngine->CameraLocation.X < 0)
	{
		RenderEngine->CameraLocation.X = 0;
	}
	if (RenderEngine->CameraLocation.X  > WorldInstance->WorldSize - RenderEngine->CameraSize.X)
	{
		RenderEngine->CameraLocation.X = WorldInstance->WorldSize - RenderEngine->CameraSize.X;
	}
	if (RenderEngine->CameraLocation.Y < 0)
	{
		RenderEngine->CameraLocation.Y = 0;
	}
	if (RenderEngine->CameraLocation.Y  > WorldInstance->WorldSize - RenderEngine->CameraSize.Y)
	{
		RenderEngine->CameraLocation.Y = WorldInstance->WorldSize - RenderEngine->CameraSize.Y;
	}
}
float fpscounter = 0;
void GameManager::MainLoop()
{
	std::cout << "Start mainloop" << std::endl;
	WorldInstance->DeltaTime = 1 / 60.0;
	sf::Time elapsed = clock.restart();
	while (Running)
	{
		PollInput();
		//std::cout << "Finish Poll" << std::endl;
		Update();
		//std::cout << "Finish Update" << std::endl;
		Render();
		//std::cout << "Finish render" << std::endl;
		sf::Time elapsed = clock.restart();
//#ifndef _DEBUG
		WorldInstance->DeltaTime = elapsed.asSeconds();
//#endif
		fpscounter += WorldInstance->DeltaTime;
		if (fpscounter >= 0.2)
		{
			std::cout << 1 / WorldInstance->DeltaTime << std::endl;
			fpscounter = 0;
		}
	}
	Window.close();
}