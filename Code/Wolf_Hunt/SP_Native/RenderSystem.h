#pragma once
#include ".\..\Wolf_Hunt\World.h"
#include ".\..\Wolf_Hunt\EntityLiving.h"
#include ".\..\Wolf_Hunt\EntityGrass.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
class RenderSystem
{
public:
	Sim::Vector<float> CameraLocation;
	sf::RectangleShape Wolf;
	sf::RectangleShape Sheep;
	sf::RectangleShape Grass;
	RenderSystem();
	~RenderSystem();
	void Render(Sim::World * world, sf::RenderWindow * window);
};

