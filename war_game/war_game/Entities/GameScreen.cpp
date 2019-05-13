#include "GameScreen.h"

GameScreen::GameScreen()
{
}

int GameScreen::Run(sf::RenderWindow &App, GameManager &gm)
{
	//gm.Start();
	bool running = true;
	sf::Sprite mapSprite;
	while (running)
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return -1;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return 0;
				}
			}
			App.clear();
			gm.DrawMap(mapSprite, App);
			App.display();
		}
	}
	return -1;
}