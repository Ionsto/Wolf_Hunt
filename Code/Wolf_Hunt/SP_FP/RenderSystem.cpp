#include "RenderSystem.h"
#include <iostream>
#include <GL\glew.h>
#include "RenderSheep.h"

RenderSystem::RenderSystem(sf::RenderWindow * window)
{
	this->Window = window; 
	this->Window->setActive();
	sf::ContextSettings settings = window->getSettings();
	std::cout << "OpenGL version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
	
	CameraLocation = Sim::Vector<float>(0, 0);
	CameraSize = Sim::Vector<float>(800, 800);
	RenderTargets.emplace_back(std::make_unique<RenderSheep>());//Other
	RenderTargets.emplace_back(std::make_unique<RenderSheep>());//Wolf
	RenderTargets.emplace_back(std::make_unique<RenderSheep>());//Sheep
	RenderTargets.emplace_back(std::make_unique<RenderSheep>());//Corpse
	RenderTargets.emplace_back(std::make_unique<RenderSheep>());//Fox
}


RenderSystem::~RenderSystem()
{
}
void RenderSystem::Render(Sim::World * world)
{
	Window->setActive();
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
					RenderEntity * renderversion = RenderTargets[ent->Type].get();
					renderversion->Render(ent);
					//window->draw(Fox);
				}
			}
		}
	}
}