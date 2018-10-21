#include "GameManager.h"
#include "./../Wolf_Hunt/EntitySheep.h"
#include "./../Wolf_Hunt/EntityWolf.h"
#include "./../Wolf_Hunt/EntityFox.h"
#include <iostream>

SP_Native::GameManager::GameManager()
{
	TimeDifference = 0;
}


SP_Native::GameManager::~GameManager()
{
	RenderEngine.release();
}

void SP_Native::GameManager::Init()
{
	WorldInstance = std::make_unique<Sim::World>();
	Window.create(sf::VideoMode(1000, 1000), "My window");
	//Window.create(sf::VideoMode::getFullscreenModes()[0], "Wolf hunt SP", sf::Style::Fullscreen);
	RenderEngine = std::make_unique<RenderSystem>();
	Running = true;
	auto wolfyboi = std::make_unique<Sim::EntityWolf>(WorldInstance.get());

	std::cout << (int)wolfyboi.get()<<"\n";
	WorldInstance->AddEntity(std::move(wolfyboi));
	RenderEngine->PlayerCamera = ((Sim::EntityWolf*)(WorldInstance->EntityList.front().get()))->IDRenderVision;
	//std::cout << (int)WorldInstance->EntityList[0].get() << "\n";
	//WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(100, 100));
	
	for (int i = 0; i < 200; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<Sim::EntitySheep>(WorldInstance.get()));
		WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(rand() % WorldInstance->WorldSize, rand() % WorldInstance->WorldSize));
		((Sim::EntitySheep*)WorldInstance->EntityList[id].get())->NNInstance.Randomise(2);
		((Sim::EntitySheep*)WorldInstance->EntityList[id].get())->Age += rand() % 40;
	}
	for (int i = 0; i < 20; ++i)
	{
		int id = WorldInstance->AddEntity(std::make_unique<Sim::EntityFox>(WorldInstance.get()));
		WorldInstance->EntityList[id]->SetLocation(Sim::Vector<float>(rand() % WorldInstance->WorldSize, rand() % WorldInstance->WorldSize));
	}
	Mouse = MouseState();
	Window.setKeyRepeatEnabled(false);
	std::cout << "Init complete" << std::endl;
	GameHud = GuiHud(this);
}

void SP_Native::GameManager::DebugObjectSizes()
{
	std::cout << "Size of common classes:" << std::endl;
	std::cout << "Entity:" << sizeof(Sim::Entity) << std::endl;
	std::cout << "EntityWolf:" << sizeof(Sim::EntityWolf) << std::endl;
	std::cout << "EntitySheep:" << sizeof(Sim::EntitySheep) << std::endl;
	std::cout << "EntitySheep:" << sizeof(Sim::EntitySheep) << std::endl;
}

void SP_Native::GameManager::Update()
{
	for (int i = 0; TimeDifference >= WorldInstance->DeltaTime; TimeDifference -= WorldInstance->DeltaTime)
	{
		WorldInstance->Update();
		UpdateCamera();
	}
	GameHud.Update();
}
void SP_Native::GameManager::Render()
{
	Window.clear();
	RenderEngine->Render(WorldInstance.get(), &Window);
	GameHud.Render(&Window);
	Window.display();
}
void SP_Native::GameManager::PollInput()
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
							Sim::Vector<float> Diff = WorldInstance->EntityList[i]->Pos - ((RenderEngine->CameraLocation - (RenderEngine->CameraSize/2) ) + Mouse.Location/RenderEngine->Scale);
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
						Sim::Vector<float> Diff = WorldInstance->EntityList[i]->Pos - ((RenderEngine->CameraLocation - (RenderEngine->CameraSize / 2)) + Mouse.Location / RenderEngine->Scale);
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
			Selected->TargetLocation =(RenderEngine->CameraLocation - (RenderEngine->CameraSize / 2)) + Mouse.Location / RenderEngine->Scale;
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
	float ScaleIncrement = 1.5;
	if (KeyArray[sf::Keyboard::Equal].Key == ButtonState::GoingDown)
	{
		RenderEngine->Scale *= ScaleIncrement;
		RenderEngine->CameraSize = RenderEngine->CameraSize / ScaleIncrement;
	}
	if (KeyArray[sf::Keyboard::Dash].Key == ButtonState::GoingDown)
	{
		RenderEngine->Scale /= ScaleIncrement;
		RenderEngine->CameraSize = RenderEngine->CameraSize * ScaleIncrement;
	}

	if (KeyArray[sf::Keyboard::Escape].Key == ButtonState::GoingDown)
	{
		Running = false;
	}
	if (KeyArray[sf::Keyboard::Escape].Key == ButtonState::GoingDown)
	{
		Running = false;
	}
	if (KeyArray[sf::Keyboard::R].Key == ButtonState::GoingDown)
	{
		RenderEngine->DebugView = !RenderEngine->DebugView;
	}
}
void SP_Native::GameManager::UpdateCamera()
{
	float CameraSpeed = 500;
	if (KeyArray[sf::Keyboard::A].Key == ButtonState::Down || KeyArray[sf::Keyboard::A].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.X -= CameraSpeed * WorldInstance->DeltaTime / RenderEngine->Scale;
	}
	if (KeyArray[sf::Keyboard::D].Key == ButtonState::Down || KeyArray[sf::Keyboard::D].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.X += CameraSpeed * WorldInstance->DeltaTime / RenderEngine->Scale;
	}
	if (KeyArray[sf::Keyboard::W].Key == ButtonState::Down || KeyArray[sf::Keyboard::W].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.Y -= CameraSpeed * WorldInstance->DeltaTime / RenderEngine->Scale;
	}
	if (KeyArray[sf::Keyboard::S].Key == ButtonState::Down || KeyArray[sf::Keyboard::S].Key == ButtonState::GoingDown)
	{
		RenderEngine->CameraLocation.Y += CameraSpeed * WorldInstance->DeltaTime / RenderEngine->Scale;
	}
	if (RenderEngine->CameraLocation.X - (RenderEngine->CameraSize.X/2) < 0)
	{
		RenderEngine->CameraLocation.X = (RenderEngine->CameraSize.X / 2);
	}
	if (RenderEngine->CameraLocation.X + (RenderEngine->CameraSize.X / 2) > WorldInstance->WorldSize)
	{
		RenderEngine->CameraLocation.X = WorldInstance->WorldSize - (RenderEngine->CameraSize.X / 2);
	}
	if (RenderEngine->CameraLocation.Y - (RenderEngine->CameraSize.Y / 2) < 0)
	{
		RenderEngine->CameraLocation.Y = (RenderEngine->CameraSize.Y / 2);
	}
	if (RenderEngine->CameraLocation.Y + (RenderEngine->CameraSize.Y / 2) > WorldInstance->WorldSize )
	{
		RenderEngine->CameraLocation.Y = WorldInstance->WorldSize - (RenderEngine->CameraSize.Y / 2);
	}
	if (RenderEngine->CameraSize.X > WorldInstance->WorldSize)
	{
		RenderEngine->CameraLocation.X = WorldInstance->WorldSize / 2;
	}
	if (RenderEngine->CameraSize.Y > WorldInstance->WorldSize)
	{
		RenderEngine->CameraLocation.Y = WorldInstance->WorldSize / 2;
	}
}
float fpscounter = 0;
int fpsintcounter = 0;
void SP_Native::GameManager::MainLoop()
{
	std::cout << "Start mainloop" << std::endl;
	WorldInstance->DeltaTime = 1 / 60.0;
	TimeDifference = 0;
	sf::Time elapsed = clock.restart();
	while (Running)
	{
		auto Start = Clock.now();
		PollInput();
		//std::cout << "Finish Poll" << std::endl;
		//std::cout << "Finish Update" << std::endl;
		Render();
		//std::cout << "Finish render" << std::endl;
		//sf::Time elapsed = clock.restart();
//#ifndef _DEBUG
		auto delta = clock.restart().asSeconds();
		TimeDifference += delta;
		//TimeDifference += std::chrono::duration_cast<std::chrono::duration<float>>(Clock.now() - Start).count();//elapsed.asSeconds();
//#endif
		Update();
		fpscounter += delta;
		fpsintcounter++;
		if (fpscounter >= 0.2)
		{
			//Frame time
			std::cout << fpscounter / fpsintcounter << std::endl;
			fpscounter = 0;
			fpsintcounter = 0;
		}
	}
	Window.close();
}