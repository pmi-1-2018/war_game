#include "GameScreen.h"

GameScreen::GameScreen()
{
}

int GameScreen::Run(sf::RenderWindow &App, GameManager &gm)
{
	//sf::View view;
	/*view.setSize(sf::Vector2f(975, 480));
	view.setCenter(sf::Vector2f(0, 0));*/
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
			/*if (event.type == sf::Event::MouseMoved)
			{
			
			}*/
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				App.setView(sf::View(visibleArea));
			}
			App.clear();
			//App.setView(view);
			gm.DrawMap(mapSprite, App);
			App.display();
		}
	}
	return -1;
}