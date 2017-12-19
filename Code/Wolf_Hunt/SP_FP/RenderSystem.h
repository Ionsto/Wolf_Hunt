#pragma once
#include ".\..\Wolf_Hunt\World.h"
#include ".\..\Wolf_Hunt\EntityLiving.h"
#include ".\..\Wolf_Hunt\EntityGrass.h"
#include ".\..\Wolf_Hunt\EntityCorpse.h"
#include "GuiHud.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
class RenderSystem
{
public:
	Sim::Vector<float> CameraLocation;
	Sim::Vector<float> CameraSize;
	sf::Texture WolfTexture;
	sf::Texture SheepTexture;
	sf::Texture GrassTexture;
	sf::Texture CorpseTexture;
	sf::Texture FoxTexture;
	sf::Sprite Wolf;
	sf::Sprite Sheep;
	sf::Sprite Grass;
	sf::Sprite Corpse;
	sf::Sprite Fox;
	RenderSystem();
	~RenderSystem();
	void Render(Sim::World * world, sf::RenderWindow * window);
};

