#include "RenderSystem.h"
#include <iostream>


RenderSystem::RenderSystem()
{
	CameraLocation = Sim::Vector<float>(0, 0);
	CameraSize = Sim::Vector<float>(800, 800);
	WolfTexture = sf::Texture();
	WolfTexture.loadFromFile("./Res/Entities/Wolf/Static.png");
	Wolf = sf::Sprite();
	Wolf.setTexture(WolfTexture, true);
	Wolf.setOrigin(WolfTexture.getSize().x / 2, WolfTexture.getSize().y / 2);
	SheepTexture.loadFromFile("./Res/Entities/Sheep/Static.png");
	Sheep = sf::Sprite();
	Sheep.setTexture(SheepTexture, true);
	Sheep.setOrigin(SheepTexture.getSize().x / 2, SheepTexture.getSize().y / 2);
	GrassTexture.loadFromFile("./Res/Entities/Grass/Static.png");
	Grass = sf::Sprite();
	Grass.setTexture(GrassTexture, true);
	Grass.setOrigin(GrassTexture.getSize().x / 2, GrassTexture.getSize().y / 2);
	CorpseTexture.loadFromFile("./Res/Entities/Corpse/Static.png");
	Corpse = sf::Sprite();
	Corpse.setTexture(CorpseTexture, true);
	Corpse.setOrigin(CorpseTexture.getSize().x / 2, CorpseTexture.getSize().y / 2);
	FoxTexture.loadFromFile("./Res/Entities/Fox/Static.png");
	Fox = sf::Sprite();
	Fox.setTexture(FoxTexture, true);
	Fox.setOrigin(FoxTexture.getSize().x / 2, CorpseTexture.getSize().y / 2);
}


RenderSystem::~RenderSystem()
{
}
void RenderSystem::Render(Sim::World * world, sf::RenderWindow * window)
{
	const float PI = 3.14159;
	for (int i = 0; i < world->EntityCount; ++i)
	{
		if (world->EntityList[i])
		{
			if (world->EntityList[i]->Alive)
			{
				//Render
				if (dynamic_cast<Sim::EntityLiving*>(world->EntityList[i].get()) != nullptr)
				{
					Sim::EntityLiving* ent = (Sim::EntityLiving*)world->EntityList[i].get();
					switch (ent->Type)
					{
					case Sim::EntityLiving::EntityTypes::Wolf:
						Wolf.setRotation(ent->Rot * (180.0 / PI));
						Wolf.setPosition(ent->Pos.X - CameraLocation.X, ent->Pos.Y - CameraLocation.Y);
						window->draw(Wolf);
						//render wolf
						break;
					case Sim::EntityLiving::EntityTypes::Sheep:
						//render sheep
						Sheep.setRotation(ent->Rot * (180 / PI));
						Sheep.setPosition(ent->Pos.X - CameraLocation.X, ent->Pos.Y - CameraLocation.Y);
						window->draw(Sheep);
						break;
					case Sim::EntityLiving::EntityTypes::Fox:
						//render sheep
						Fox.setRotation(ent->Rot * (180 / PI));
						Fox.setPosition(ent->Pos.X - CameraLocation.X, ent->Pos.Y - CameraLocation.Y);
						window->draw(Fox);
						break;
					}
				}
				if (dynamic_cast<Sim::EntityGrass*>(world->EntityList[i].get()) != nullptr)
				{
					Grass.setPosition(world->EntityList[i].get()->Pos.X - CameraLocation.X, world->EntityList[i].get()->Pos.Y - CameraLocation.Y);
					if (dynamic_cast<Sim::EntityGrass*>(world->EntityList[i].get())->Grown)
					{
						//Grass.setFillColor(sf::Color(0, 255, 0, 255));
					}
					else
					{
						//Grass.setFillColor(sf::Color(0, 120, 0, 255));
					}
					window->draw(Grass);
				}
				if (dynamic_cast<Sim::EntityCorpse*>(world->EntityList[i].get()) != nullptr)
				{
					Corpse.setPosition(world->EntityList[i].get()->Pos.X - CameraLocation.X, world->EntityList[i].get()->Pos.Y - CameraLocation.Y);
					window->draw(Corpse);
				}
			}
		}
	}
}