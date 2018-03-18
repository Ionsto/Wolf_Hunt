#pragma once
#include ".\..\Wolf_Hunt\Vector.h"
#include ".\..\Wolf_Hunt\World.h"
#include ".\..\Wolf_Hunt\EntityLiving.h"
#include ".\..\Wolf_Hunt\EntityGrass.h"
#include ".\..\Wolf_Hunt\EntityCorpse.h"
#include ".\..\Wolf_Hunt\SystemRender.h"
#include "GuiHud.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
namespace SP_Native {
	class RenderSystem
	{
	public:
		float Scale = 1;
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
		sf::CircleShape RayHit;
		Sim::ComponentIDRenderCamera PlayerCamera;
		RenderSystem();
		virtual ~RenderSystem();
		void Render(Sim::World * world, sf::RenderWindow * window);
		void RenderRays(Sim::ComponentRenderCamera & camera, sf::RenderWindow * window);
		void RenderSprites(Sim::World * world, sf::RenderWindow * window);
		sf::Color RayToRGB(Sim::ComponentRenderRay & ray);
	};
}

