#include "GuiHud.h"
#include "GameManager.h"


SP_Native::GuiHud::GuiHud(GameManager * newgm)
{
	gm = newgm;
	Health = sf::RectangleShape(sf::Vector2f(100,20));
	Health.setPosition(0, 0);
	Health.setFillColor(sf::Color(255,0,0,255));
	Energy = sf::RectangleShape(sf::Vector2f(100, 20));
	Energy.setPosition(0, 20);
	Energy.setFillColor(sf::Color(0, 0, 255, 255));
	LeapTime = sf::RectangleShape(sf::Vector2f(100, 20));
	LeapTime.setPosition(0, 40);
	LeapTime.setFillColor(sf::Color(0, 255, 0, 255));
}


SP_Native::GuiHud::~GuiHud()
{
}

void SP_Native::GuiHud::Update()
{
	if (gm->Selected != nullptr)
	{
		Health.setSize(sf::Vector2f(gm->Selected->Health, 20));
		Energy.setSize(sf::Vector2f(gm->Selected->Energy, 20));
		LeapTime.setSize(sf::Vector2f(100* (1-(gm->Selected->LeapCooldownTimer / gm->Selected->LeapCooldown)), 20));
	}
}

void SP_Native::GuiHud::Render(sf::RenderWindow * window)
{
	if (gm->Selected != nullptr)
	{
		window->draw(Health);
		window->draw(Energy);
		window->draw(LeapTime);
	}
}