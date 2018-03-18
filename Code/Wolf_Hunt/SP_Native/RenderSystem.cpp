#include "RenderSystem.h"
#include <iostream>


SP_Native::RenderSystem::RenderSystem()
{
	CameraSize = Sim::Vector<float>(1000, 1000);
	CameraLocation = CameraSize/2;
	Scale = 1;
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
	RayHit = sf::CircleShape(2);
}


SP_Native::RenderSystem::~RenderSystem()
{
}
void SP_Native::RenderSystem::Render(Sim::World * world, sf::RenderWindow * window)
{
	RenderSprites(world, window);
	RenderRays(world->WorldRender.GetCamera(PlayerCamera), window);
}
void SP_Native::RenderSystem::RenderSprites(Sim::World * world, sf::RenderWindow * window)
{
	Sim::Vector<float> CameraPos = CameraLocation - (CameraSize / 2);
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
						Wolf.setScale(Scale, Scale);
						Wolf.setRotation(ent->Rot * (180.0 / PI));
						Wolf.setPosition((ent->Pos.X - CameraPos.X)*Scale, (ent->Pos.Y - CameraPos.Y)*Scale);
						window->draw(Wolf);
						//render wolf
						break;
					/*case Sim::EntityLiving::EntityTypes::Sheep:
						//render sheep
						Sheep.setScale(Scale, Scale);
						Sheep.setRotation(ent->Rot * (180 / PI));
						Sheep.setPosition((ent->Pos.X - CameraPos.X)*Scale, (ent->Pos.Y - CameraPos.Y)*Scale);
						window->draw(Sheep);
						break;
					case Sim::EntityLiving::EntityTypes::Fox:
						//render sheep
						Fox.setScale(Scale, Scale);
						Fox.setRotation(ent->Rot * (180 / PI));
						Fox.setPosition((ent->Pos.X - CameraPos.X)*Scale, (ent->Pos.Y - CameraPos.Y)*Scale);
						window->draw(Fox);
						break;
					case Sim::EntityCorpse::EntityTypes::Corpse:
						//render sheep
						Corpse.setScale(Scale, Scale);
						Corpse.setRotation(ent->Rot * (180 / PI));
						Corpse.setPosition((ent->Pos.X - CameraPos.X)*Scale, (ent->Pos.Y - CameraPos.Y)*Scale);
						window->draw(Corpse);
						break;*/
					}
				}
			}
		}
	}
}

sf::Color SP_Native::RenderSystem::RayToRGB(Sim::ComponentRenderRay & ray)
{
	static const sf::Color ColourMapping[6] = { sf::Color(255,255,255),sf::Color(255,0,0),sf::Color(0,255,0),sf::Color(0,0,255),sf::Color(255,0,255),sf::Color(255,125,125)};
	auto rawcolour = ColourMapping[ray.Colour];
	static const auto maxcolour = ColourMapping[0];
	float blendfactor = ray.Distance / Sim::ComponentRenderRay::MaxDistance;
	return sf::Color(((rawcolour.r*(1 - blendfactor)) + (maxcolour.r*blendfactor)),
		((rawcolour.g*(1 - blendfactor)) + (maxcolour.g*blendfactor)),
		((rawcolour.b*(1 - blendfactor)) + (maxcolour.b*blendfactor)));
}
void SP_Native::RenderSystem::RenderRays(Sim::ComponentRenderCamera & camera, sf::RenderWindow * window)
{
	Sim::Vector<float> CameraPos = CameraLocation - (CameraSize / 2);
	static const float SampleSlice = Sim::ComponentRenderCamera::FOV / (Sim::ComponentRenderCamera::SampleCount);
	static const float HalfSampleCount = (Sim::ComponentRenderCamera::SampleCount - 1) / 2.0;
	float RayAngle = camera.Rotation - (SampleSlice*HalfSampleCount);
	for (int s = 0; s < Sim::ComponentRenderCamera::SampleCount; ++s)
	{
		RayAngle += SampleSlice;
		Sim::Vector<float> RayLocation = (camera.Position +  (Sim::Vector<float>(cos(RayAngle), sin(RayAngle))*camera.Rays[s].Distance));
		RayHit.setFillColor(RayToRGB(camera.Rays[s]));
		RayHit.setScale(Scale, Scale);
		RayHit.setPosition((RayLocation.X - CameraPos.X)*Scale, (RayLocation.Y - CameraPos.Y)*Scale);
		window->draw(RayHit);
	}

}