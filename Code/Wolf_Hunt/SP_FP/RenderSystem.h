#pragma once
#include <GL\glew.h>
#include <GL\wglew.h>
#include ".\..\Wolf_Hunt\World.h"
#include ".\..\Wolf_Hunt\EntityLiving.h"
#include ".\..\Wolf_Hunt\EntityGrass.h"
#include ".\..\Wolf_Hunt\EntityCorpse.h"
#include "GuiHud.h"
#include "RenderEntity.h"
#include "RenderScene.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
class RenderSystem
{
public:
	std::unique_ptr<RenderCamera> camera;
	sf::RenderWindow * Window;
	RenderSystem(sf::RenderWindow * window);
	virtual ~RenderSystem();
	void Render(Sim::World * world);
};

