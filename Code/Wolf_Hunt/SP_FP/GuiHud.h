#pragma once
#include <SFML/Graphics.hpp>
class GameManager;
class GuiHud
{
public:
	sf::RectangleShape Health;
	sf::RectangleShape Energy;
	sf::RectangleShape LeapTime;
	GameManager * gm;
	GuiHud(GameManager * gm = nullptr);
	virtual ~GuiHud();
	void Update();
	void Render(sf::RenderWindow * window);
};

