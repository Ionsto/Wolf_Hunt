#include "RenderSystem.h"



RenderSystem::RenderSystem()
{
	Wolf = sf::RectangleShape();
	Wolf.setSize(sf::Vector2f(20, 20));
	Wolf.setOrigin(sf::Vector2f(5, 5));
	Wolf.setFillColor(sf::Color(255, 0, 0, 255));
	Sheep = sf::RectangleShape();
	Sheep.setSize(sf::Vector2f(20, 20));
	Sheep.setOrigin(sf::Vector2f(5, 5));
	Sheep.setFillColor(sf::Color(255, 0, 255, 255));
	Grass = sf::RectangleShape();
	Grass.setSize(sf::Vector2f(5, 5));
	Grass.setOrigin(sf::Vector2f(5, 5));
	Grass.setFillColor(sf::Color(0, 255, 0, 255));
}


RenderSystem::~RenderSystem()
{
}
void RenderSystem::Render(Sim::World * world, sf::RenderWindow * window)
{
	for (int i = 0; i < world->EntityCount; ++i)
	{
		if (world->EntityList[i])
		{
			if (world->EntityList[i]->Alive)
			{
				//Render
				if (dynamic_cast<Sim::EntityLiving*>(world->EntityList[i].get()) != NULL)
				{
					Sim::EntityLiving* ent = (Sim::EntityLiving*)world->EntityList[i].get();
					switch (ent->Type)
					{
					case Sim::EntityLiving::EntityTypes::Wolf:
						Wolf.setPosition(ent->Pos.X, ent->Pos.Y);
						window->draw(Wolf);
						//render wolf
						break;
					case Sim::EntityLiving::EntityTypes::Sheep:
						//render sheep
						Sheep.setPosition(ent->Pos.X, ent->Pos.Y);
						window->draw(Sheep);
						break;
					}
				}
				if (dynamic_cast<Sim::EntityGrass*>(world->EntityList[i].get()) != NULL)
				{
					Grass.setPosition(world->EntityList[i].get()->Pos.X, world->EntityList[i].get()->Pos.Y);
					if (dynamic_cast<Sim::EntityGrass*>(world->EntityList[i].get())->Grown)
					{
						Grass.setFillColor(sf::Color(0, 255, 0, 255));
					}
					else
					{
						Grass.setFillColor(sf::Color(0, 120, 0, 255));
					}
					window->draw(Grass);
				}
			}
		}
	}
}